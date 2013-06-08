//===========================================================================//
//  FILE:  SingleEquipmentConfigChildWnd.h									//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	单站对象配置ChildFrame。												//
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
#pragma once

// SingleEquipmentConfigChildWnd frame with splitter

class SingleEquipmentConfigChildWnd : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(SingleEquipmentConfigChildWnd)

private:
	/*对象树和对象实例View的分割条*/
	CSplitterWndEx objectTreeAndInstanceSplitterWnd;

	/*对象实例和下部的操作命令、输出View分割条*/
	CSplitterWndEx objectInstanceAndOperationSplitterWnd;

	/*操作命令和输出View的分割条*/
	CSplitterWndEx objectOperationAndOutputSplitterWnd;

public:
	SingleEquipmentConfigChildWnd();           
	virtual ~SingleEquipmentConfigChildWnd();

public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

protected:
	BOOL CreateObjectTreeAndInstanceSplitterWnd(CRect& clientRect, CCreateContext* pContext);

	BOOL  CreateObjectInstanceAndOperationSplitterWnd(CRect& clientRect, CCreateContext* pContext);

	BOOL CreateObjectOperationAndOutputSplitterWnd(CRect& clientRect, CCreateContext* pContext);

protected:
	DECLARE_MESSAGE_MAP()
};


