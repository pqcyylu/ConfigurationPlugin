//===========================================================================//
//  FILE:  SingleEquipmentConfigPlugin.h									//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	��վ�������ò���ӿڡ�													//
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
	/*����������*/
	/*��ѯ����Ƿ���Ҫֲ���ȱʡ������*/
	virtual BOOL HasDefaultToolBar();

	/*��ѯ����Ƿ���Ҫֲ����ĵ�������*/
	virtual BOOL HasDocumentToolBar();

	virtual void InitPlugInHostModule(); 

	/*����ȱʡ������*/
	virtual BOOL LoadDefaultToolBarEx(CMFCToolBar* pLoadToolBar);

	/*����ȱʡ��������Title*/
	virtual CString GetDefaultToolBarTitle();

	/*������Document/View��Ӧ�Ĺ�����*/
	virtual BOOL LoadDocumentToolBarEx(CMFCToolBar* pLoadToolBar);

	/*�����ĵ���������Title*/
	virtual CString GetDocumentToolBarTitle();

	/*�õ������MVCģ����*/
	virtual CDTMultiDocTemplate* CreateDocTemplate();

	/*�õ���ǰҪ�������ĵ���*/
	CString GetCreateDocumentName();

	CDocument* GetDocument(const CString& documentName);

protected:

	afx_msg void OnOpenSingleCfg();

	afx_msg void OnUpdateOpenSingleCfgUI(CCmdUI* pCmdUI);
};


