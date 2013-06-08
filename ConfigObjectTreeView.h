//===========================================================================//
//  FILE:  ConfigObjectTreeView.h											//
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
#pragma once

#include "afxcmn.h"
// ConfigObjectTreeView form view

class ConfigObjectTreeView : public CFormView
{
	DECLARE_DYNCREATE(ConfigObjectTreeView)

protected:
	ConfigObjectTreeView();           // protected constructor used by dynamic creation
	virtual ~ConfigObjectTreeView();

private:
	CMFCToolBar findToolBar;

	CTreeCtrl configObjectTreeCtrl;

	CImageList configObjectImages;

	CStatic objectTreeGroup;

public:
	enum { IDD = IDD_CONFIGOBJECTTREEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void OnChangeVisualStyle();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnTreeItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnConfigObjectTreeDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	void AdjustLayout();
};


