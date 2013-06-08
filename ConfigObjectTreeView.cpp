//===========================================================================//
//  FILE:  ConfigObjectTreeView.cpp											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	网元信息模型的树View。													//
//																			//
//------------------------------------------------------------------------	//
//  AUTHOR: datangmobile LMT-B 	pengqiang	    							//
//			pengqiang@datangmobile.cn	TEL: +86 10 58833109.   			//
//	Copyright:																//
// Copyright (c) 2005-2015, DatangMobile Corporation.  All rights reserved.	//
//	---------------------------------------------------------------------	//
//	Note:                    												//
//			                                         						//
//			                                                            	//
//-----------------------------------------------------------------------	//
//	 HISTORY:																//
//	 2013-05-16 - create by pengqiang										//
//==========================================================================//

#include "stdafx.h"
#include "resource.h"
#include "ConfigObjectTreeView.h"
#include "ConfigDocumentBase.h"
#include "ConfigObjectTreeLoader.h"
#include "ConfigObjectViewModel.h"
#include "AveLogMacro.h"
#include "ControlLayoutHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ConfigObjectTreeView
IMPLEMENT_DYNCREATE(ConfigObjectTreeView, CFormView)

ConfigObjectTreeView::ConfigObjectTreeView()
	: CFormView(ConfigObjectTreeView::IDD)
{

}

ConfigObjectTreeView::~ConfigObjectTreeView()
{
}

void ConfigObjectTreeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIGOBJECT_TREE, configObjectTreeCtrl);
	DDX_Control(pDX, IDC_STATIC_GROUP_OBJS, objectTreeGroup);
}

BEGIN_MESSAGE_MAP(ConfigObjectTreeView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_CONFIGOBJECT_TREE, OnTreeItemExpanded)
	ON_NOTIFY(NM_DBLCLK, IDC_CONFIGOBJECT_TREE, OnConfigObjectTreeDoubleClick)
END_MESSAGE_MAP()


// ConfigObjectTreeView diagnostics

#ifdef _DEBUG
void ConfigObjectTreeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ConfigObjectTreeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ConfigObjectTreeView message handlers
int ConfigObjectTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ShowScrollBar(SB_BOTH,FALSE);
	// TODO:  Add your specialized creation code here
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	findToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_CONFIGOBJECT_TREE_TOOLBAR);
	findToolBar.LoadToolBar(IDR_CONFIGOBJECT_TREE_TOOLBAR, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	findToolBar.SetPaneStyle(findToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	findToolBar.SetPaneStyle(findToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	findToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	findToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

void ConfigObjectTreeView::OnChangeVisualStyle()
{
	if(configObjectTreeCtrl.GetSafeHwnd() == NULL)
		return;

	configObjectImages.DeleteImageList();

	//UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;
	UINT uiBmpId = IDB_CONFIGOBJECT_HC;

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

	configObjectImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	configObjectImages.Add(&bmp, RGB(255, 0, 0));

	configObjectTreeCtrl.SetImageList(&configObjectImages, TVSIL_NORMAL);
}


void ConfigObjectTreeView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	AdjustLayout();
}

void ConfigObjectTreeView::AdjustLayout()
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
	if(objectTreeGroup.GetSafeHwnd() != NULL)
	{
		groupTextHeight = ControlLayoutHelper::CalculateHeaderTextHeight(objectTreeGroup);

		objectTreeGroup.SetWindowPos(NULL, 0, 0, rectClient.Width()+1, rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	int cyTlb = findToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	findToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top+groupTextHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	if(configObjectTreeCtrl.GetSafeHwnd() != NULL)
	{
		configObjectTreeCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + groupTextHeight + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - groupTextHeight- cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void ConfigObjectTreeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	OnChangeVisualStyle();

	ConfigDocumentBase* configDocument = DYNAMIC_DOWNCAST(ConfigDocumentBase, GetDocument());
	if(NULL == configDocument)
	{
		L_ERROR("获取配置对象Document失败，无法加载配置对象树！");
		return;
	}

	ConfigObjectTreeLoader::LoadRootNode(configDocument, &configObjectTreeCtrl);
}

void ConfigObjectTreeView::OnTreeItemExpanded(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW nmTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;

	if(NULL == nmTreeView)
	{
		return;
	}

	ConfigDocumentBase* configDocument = DYNAMIC_DOWNCAST(ConfigDocumentBase, GetDocument());
	if(NULL == configDocument)
	{
		L_ERROR("获取配置对象Document失败，无法加载子对象！");
		return;
	}

	if(nmTreeView->action != TVE_EXPAND)
	{
		return;
	}

	HTREEITEM hExpandItem = nmTreeView->itemNew.hItem;

	ConfigObjectTreeLoader::LoadChildNode(configDocument, &configObjectTreeCtrl, hExpandItem);
}

void ConfigObjectTreeView::OnConfigObjectTreeDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	UINT uFlags; 
	CPoint pt; 
	GetCursorPos(&pt); 
	configObjectTreeCtrl.ScreenToClient(&pt); 

	HTREEITEM hItem = configObjectTreeCtrl.HitTest(pt,&uFlags); 

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags)) 
	{
		ConfigObjectViewModel* selectedObjectViewModel = (ConfigObjectViewModel*)configObjectTreeCtrl.GetItemData(hItem);

		ConfigDocumentBase* configDocument = DYNAMIC_DOWNCAST(ConfigDocumentBase, GetDocument());
		if(NULL == configDocument)
		{
			L_ERROR("获取配置对象Document失败，无法加载子对象！");
			return;
		}

		configDocument->SetSelectedConfigObjectViewModel(selectedObjectViewModel);
	}

	*pResult = TRUE;
}
