// ConfigObjectOperationTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include <boost/foreach.hpp>
#include "ConfigObjectOperationTreeView.h"
#include "ControlLayoutHelper.h"
#include "NetElementViewModelInc/NetElementViewModelExport.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "ConfigObjectViewModel.h"
#include "OperationTreeLoader.h"
#include "ConfigDocumentBase.h"
#include "ConfigObjectOperationHandler.h"
#include "AveLogMacro.h"


// ConfigObjectOperationTreeView

IMPLEMENT_DYNCREATE(ConfigObjectOperationTreeView, CFormView)

ConfigObjectOperationTreeView::ConfigObjectOperationTreeView()
	: CFormView(ConfigObjectOperationTreeView::IDD)
{

}

ConfigObjectOperationTreeView::~ConfigObjectOperationTreeView()
{
}

void ConfigObjectOperationTreeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OBJOPERATION_GROUP, operationGroupCtrl);
	DDX_Control(pDX, IDC_OPERATION_TREE, operationTreeCtrl);
}

BEGIN_MESSAGE_MAP(ConfigObjectOperationTreeView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_OPERATION_TREE, OnOperationTreeDoubleClick)
END_MESSAGE_MAP()


// ConfigObjectOperationTreeView ���

#ifdef _DEBUG
void ConfigObjectOperationTreeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ConfigObjectOperationTreeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ConfigObjectOperationTreeView ��Ϣ�������


void ConfigObjectOperationTreeView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AdjustLayout();
}

void ConfigObjectOperationTreeView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	ShowScrollBar(SB_BOTH,FALSE);

	CRect rectClient;
	GetClientRect(rectClient);

	/*������ʾ�ı�����������󣺡����ı��߶ȣ��������и��ؼ�*/
	int groupTextHeight = 0;
	if(operationGroupCtrl.GetSafeHwnd() != NULL)
	{
		groupTextHeight = ControlLayoutHelper::CalculateHeaderTextHeight(operationGroupCtrl);

		operationGroupCtrl.SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	if(operationTreeCtrl.GetSafeHwnd() != NULL)
	{
		operationTreeCtrl.SetWindowPos(NULL, rectClient.left+1, rectClient.top+groupTextHeight+1, rectClient.Width()-2, rectClient.Height()-groupTextHeight-2, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void ConfigObjectOperationTreeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	LoadImageList();
}

void ConfigObjectOperationTreeView::UpdateView(ConfigObjectViewModel* selectedCfgObjViewModel)
{
	operationTreeCtrl.DeleteAllItems();

	if(NULL == selectedCfgObjViewModel)
		return;

	OperationTreeLoader::LoadOpeartions(*selectedCfgObjViewModel, operationTreeCtrl);

	Invalidate();
}

void ConfigObjectOperationTreeView::LoadImageList()
{
	if(operationTreeCtrl.GetSafeHwnd() == NULL)
		return;

	operationImages.DeleteImageList();

	//UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;
	UINT uiBmpId = IDB_OPERATION_BMP;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	//nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;
	nFlags |= ILC_COLOR24;

	operationImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);

	operationImages.Add(&bmp, RGB(192,192,192));

	operationTreeCtrl.SetImageList(&operationImages, TVSIL_NORMAL);
}

void ConfigObjectOperationTreeView::OnOperationTreeDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	/*��ֹ˫�����ڵ���չ�������۵�����*/
	*pResult = TRUE;

	/*��˫���Ĳ����ڵ��л�ȡ��������Ϣ*/
	UINT uFlags; 
	CPoint pt; 
	GetCursorPos(&pt); 
	operationTreeCtrl.ScreenToClient(&pt); 

	HTREEITEM hItem = operationTreeCtrl.HitTest(pt,&uFlags); 

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags)) 
	{
		IMibCommand* selectedCommand = (IMibCommand*)operationTreeCtrl.GetItemData(hItem);
		if(NULL == selectedCommand)
		{
			L_ERROR("��ȡ�������selectedCommandʧ�ܣ��޷����к����������!");
			return;
		}

		ConfigDocumentBase* configDocument = DYNAMIC_DOWNCAST(ConfigDocumentBase, GetDocument());
		if(NULL == configDocument)
		{
			L_ERROR("��ȡ���ö���Documentʧ�ܣ��޷����к����������");
			return;
		}

		ConfigObjectOperationHandler::GetInstance()->HandleOperation(*selectedCommand, *configDocument);
		//configDocument->SetSelectedConfigObjectViewModel(selectedObjectViewModel);
	}
}
