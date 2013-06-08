//===========================================================================//
//  FILE:  SingleEquipmentConfigChildWnd.h									//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	��վ��������ChildFrame��												//
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
	/*�������Ͷ���ʵ��View�ķָ���*/
	CSplitterWndEx objectTreeAndInstanceSplitterWnd;

	/*����ʵ�����²��Ĳ���������View�ָ���*/
	CSplitterWndEx objectInstanceAndOperationSplitterWnd;

	/*������������View�ķָ���*/
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


