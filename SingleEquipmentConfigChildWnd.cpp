//===========================================================================//
//  FILE:  SingleEquipmentConfigChildWnd.cpp									//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	单站对象配置的ChildFrame。												//
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
#include "SingleEquipmentConfigChildWnd.h"
#include "ConfigObjectTreeView.h"
#include "ConfigObjectOperationTreeView.h"
#include "ConfigObjectOutPutView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// SingleEquipmentConfigChildWnd
IMPLEMENT_DYNCREATE(SingleEquipmentConfigChildWnd, CMDIChildWndEx)

SingleEquipmentConfigChildWnd::SingleEquipmentConfigChildWnd()
{

}

SingleEquipmentConfigChildWnd::~SingleEquipmentConfigChildWnd()
{
}

BEGIN_MESSAGE_MAP(SingleEquipmentConfigChildWnd, CMDIChildWndEx)
END_MESSAGE_MAP()


BOOL SingleEquipmentConfigChildWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect clientRect(0, 0, lpcs->cx, lpcs->cy);

	//创建对象树和实例窗口的左右分割条
	if(!CreateObjectTreeAndInstanceSplitterWnd(clientRect, pContext))
	{
		return FALSE;
	}

	//创建实例窗口和操作窗口的上下分割条
	if(!CreateObjectInstanceAndOperationSplitterWnd(clientRect, pContext))
	{
		return FALSE;
	}

	//创建操作窗口和输出窗口的左右分割条
	if(!CreateObjectOperationAndOutputSplitterWnd(clientRect, pContext))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL SingleEquipmentConfigChildWnd::CreateObjectTreeAndInstanceSplitterWnd(CRect& clientRect, CCreateContext* pContext)
{
	int objectTreeWidth = clientRect.Width() / 4;
	int objectTreeHeight = clientRect.Height();

	//创建对象树和实例窗口的左右分割条
	if (!objectTreeAndInstanceSplitterWnd.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	//创建对象树View
	if (!objectTreeAndInstanceSplitterWnd.CreateView(0, 0,
		RUNTIME_CLASS(ConfigObjectTreeView), CSize(objectTreeWidth, objectTreeHeight), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	clientRect.DeflateRect(objectTreeWidth, 0);

	return TRUE;
}

BOOL SingleEquipmentConfigChildWnd::CreateObjectInstanceAndOperationSplitterWnd(CRect& clientRect, CCreateContext* pContext)
{
	int instanceViewWidth = clientRect.Width();

	int instanceViewHeight = ( clientRect.Height() / 3 ) *2;

	//创建实例窗口和下部操作窗口的上下分割条
	if (!objectInstanceAndOperationSplitterWnd.CreateStatic(
		&objectTreeAndInstanceSplitterWnd,     // our parent window is the first splitter
		2, 1,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		objectTreeAndInstanceSplitterWnd.IdFromRowCol(0, 1)
		// new splitter is in the first row, 2nd column of first splitter
		))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	//创建实例窗口View
	if (!objectInstanceAndOperationSplitterWnd.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(instanceViewWidth, instanceViewHeight), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	clientRect.DeflateRect(0, instanceViewHeight);

	return TRUE;
}

BOOL SingleEquipmentConfigChildWnd::CreateObjectOperationAndOutputSplitterWnd(CRect& clientRect, CCreateContext* pContext)
{
	int operationTreeViewWidth = clientRect.Width() / 3;
	int operationTreeViewHeight = clientRect.Height();

	if (!objectOperationAndOutputSplitterWnd.CreateStatic(&objectInstanceAndOperationSplitterWnd,
		1, 2,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		objectInstanceAndOperationSplitterWnd.IdFromRowCol(1, 0)))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	//创建操作树
	if(!objectOperationAndOutputSplitterWnd.CreateView(0, 0, 
		RUNTIME_CLASS(ConfigObjectOperationTreeView), CSize(operationTreeViewWidth, operationTreeViewHeight),  pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	//创建操作结果输出窗口
	int outPutViewWidth = clientRect.Width() - operationTreeViewWidth;
	if(!objectOperationAndOutputSplitterWnd.CreateView(0, 1, 
		RUNTIME_CLASS(ConfigObjectOutPutView), CSize(outPutViewWidth, operationTreeViewHeight),  pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	return TRUE;
}

