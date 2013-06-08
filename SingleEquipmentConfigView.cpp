// SingleEquipmentConfigView.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ConfigurationPluginMessageDefine.h"
#include "SingleEquipmentConfigView.h"
#include "ControlLayoutHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_CONFIG_GRID_CTRL 1
// SingleEquipmentConfigView

IMPLEMENT_DYNCREATE(SingleEquipmentConfigView, CFormView)

SingleEquipmentConfigView::SingleEquipmentConfigView()
	: CFormView(SingleEquipmentConfigView::IDD)
{

}

SingleEquipmentConfigView::~SingleEquipmentConfigView()
{
}

void SingleEquipmentConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INSTANCE_GROUP, instanceGroup);
}

BEGIN_MESSAGE_MAP(SingleEquipmentConfigView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_UPDATE_INSTANCES_VIEW, OnUpdateView)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK, OnConfigGridContrlDoubleClick)
END_MESSAGE_MAP()


// SingleEquipmentConfigView diagnostics

#ifdef _DEBUG
void SingleEquipmentConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SingleEquipmentConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SingleEquipmentConfigView message handlers

int SingleEquipmentConfigView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	ShowScrollBar(SB_BOTH,FALSE);

	CRect rectClient;
	GetClientRect (rectClient);

	if(!configObjectGridCtrl.Create(WS_CHILD, rectClient, this, ID_CONFIG_GRID_CTRL))
	{
		ASSERT(0);
		return -1;
	}

	configObjectGridCtrl.ShowWindow(1);

	AdjustLayout();

	return 0;
}


void SingleEquipmentConfigView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	AdjustLayout();
}

void SingleEquipmentConfigView::AdjustLayout()
{
	ShowScrollBar(SB_BOTH,FALSE);

	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	if(instanceGroup.GetSafeHwnd() != NULL)
	{
		instanceGroup.SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	/*计算提示文本串“管理对象：”的文本高度，用于排列各控件*/
	int groupTextHeight = 0;
	if(instanceGroup.GetSafeHwnd() != NULL)
	{
		groupTextHeight = ControlLayoutHelper::CalculateHeaderTextHeight(instanceGroup);
	}

	if(configObjectGridCtrl.GetSafeHwnd() != NULL)
	{
		configObjectGridCtrl.SetWindowPos(NULL,  2,  groupTextHeight,  rectClient.Width()-4,  rectClient.Height()-groupTextHeight-2,
			SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void SingleEquipmentConfigView::UpdateView(IMibInstanceTablePtr instanceTablePtr)
{
	SendMessage(WM_UPDATE_INSTANCES_VIEW, (WPARAM)(&instanceTablePtr));
}

LRESULT SingleEquipmentConfigView::OnUpdateView(WPARAM wpInstanceTable, LPARAM lpParam)
{
	CWaitCursor waitting;

	IMibInstanceTablePtr instanceTablePtr(*(IMibInstanceTablePtr*)wpInstanceTable);
	if(NULL == instanceTablePtr)
		return 0;

	configObjectGridCtrl.UpdateView(instanceTablePtr);

	return 0;
}

LRESULT SingleEquipmentConfigView::OnConfigGridContrlDoubleClick(WPARAM wParam, LPARAM lParam)
{
	IMibInstance* selectedInstance = GetInstanceFromSelectedItem((CBCGPGridItem*)lParam);
	if(NULL == selectedInstance)
		return 0;






	return 0;
}

IMibInstance* SingleEquipmentConfigView::GetInstanceFromSelectedItem(CBCGPGridItem* selectedGridItem)
{
	if(NULL == selectedGridItem)
		return NULL;

	CBCGPGridRow* selectedRow = selectedGridItem->GetParentRow();
	if(NULL == selectedRow)
		return NULL;

	IMibInstance* selectInstance = (IMibInstance*)selectedRow->GetData();
	
	return selectInstance;
}