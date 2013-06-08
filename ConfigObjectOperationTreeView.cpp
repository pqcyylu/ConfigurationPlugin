// ConfigObjectOperationTreeView.cpp : 实现文件
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


// ConfigObjectOperationTreeView 诊断

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


// ConfigObjectOperationTreeView 消息处理程序


void ConfigObjectOperationTreeView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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

	/*计算提示文本串“管理对象：”的文本高度，用于排列各控件*/
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

	// TODO: 在此添加专用代码和/或调用基类
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
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
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
	/*防止双击树节点是展开或则折叠子树*/
	*pResult = TRUE;

	/*从双击的操作节点中获取到命令信息*/
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
			L_ERROR("获取命令对象selectedCommand失败，无法进行后续的命令处理!");
			return;
		}

		ConfigDocumentBase* configDocument = DYNAMIC_DOWNCAST(ConfigDocumentBase, GetDocument());
		if(NULL == configDocument)
		{
			L_ERROR("获取配置对象Document失败，无法进行后续的命令处理！");
			return;
		}

		ConfigObjectOperationHandler::GetInstance()->HandleOperation(*selectedCommand, *configDocument);
		//configDocument->SetSelectedConfigObjectViewModel(selectedObjectViewModel);
	}
}
