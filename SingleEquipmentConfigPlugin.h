//===========================================================================//
//  FILE:  SingleEquipmentConfigPlugin.h									//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	单站对象配置插件接口。													//
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


// SingleEquipmentConfigPlugin
class SingleEquipmentConfigPlugin : public CDTPlugInBase
{
	DECLARE_SERIAL(SingleEquipmentConfigPlugin)

protected:
	SingleEquipmentConfigPlugin();

public:
	DECLARE_MESSAGE_MAP()

public:
	virtual ~SingleEquipmentConfigPlugin();


protected:
	/*工具条操作*/
	/*查询插件是否有要植入的缺省工具条*/
	virtual BOOL HasDefaultToolBar();

	/*查询插件是否有要植入的文档工具条*/
	virtual BOOL HasDocumentToolBar();

	virtual void InitPlugInHostModule(); 

	/*加载缺省工具条*/
	virtual BOOL LoadDefaultToolBarEx(CMFCToolBar* pLoadToolBar);

	/*返回缺省工具条的Title*/
	virtual CString GetDefaultToolBarTitle();

	/*加载与Document/View对应的工具条*/
	virtual BOOL LoadDocumentToolBarEx(CMFCToolBar* pLoadToolBar);

	/*返回文档工具条的Title*/
	virtual CString GetDocumentToolBarTitle();

	/*得到插件的MVC模板类*/
	virtual CDTMultiDocTemplate* CreateDocTemplate();

	/*得到当前要创建的文档名*/
	CString GetCreateDocumentName();

	CDocument* GetDocument(const CString& documentName);

protected:

	afx_msg void OnOpenSingleCfg();

	afx_msg void OnUpdateOpenSingleCfgUI(CCmdUI* pCmdUI);
};


