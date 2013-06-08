//===========================================================================//
//  FILE:  SingleEquipmentConfigPlugin.cpp									//
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

#include "stdafx.h"
#include "resource.h"
#include <DTPluginFrameInc/DTPluginFrameInc.h>
#include "SingleEquipmentConfigPlugin.h"
#include "ConfigurationPluginMessageDefine.h"
#include "SingleEquipmentConfigDoc.h"
#include "SingleEquipmentConfigView.h"
#include "SingleEquipmentConfigChildWnd.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "NetElementViewModelInc/NetElementViewModelExport.h"
#include "ConfigDocumentNameUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// SingleEquipmentConfigPlugin
IMPLEMENT_SERIAL(SingleEquipmentConfigPlugin, CDTPlugInBase, 1)

SingleEquipmentConfigPlugin::SingleEquipmentConfigPlugin()
{
}

SingleEquipmentConfigPlugin::~SingleEquipmentConfigPlugin()
{
}

BEGIN_MESSAGE_MAP(SingleEquipmentConfigPlugin, CDTPlugInBase)
	ON_COMMAND(ID_CMD_OPEN_SINGLEEQUIPMENT_CFG, OnOpenSingleCfg)
	ON_UPDATE_COMMAND_UI(ID_CMD_OPEN_SINGLEEQUIPMENT_CFG, OnUpdateOpenSingleCfgUI)
END_MESSAGE_MAP()

extern AFX_EXTENSION_MODULE ConfigurationPluginDLL;

void SingleEquipmentConfigPlugin::InitPlugInHostModule()
{
	m_hPlugInHostModule = ConfigurationPluginDLL.hResource;
}

/*得到插件的MVC模板类*/
CDTMultiDocTemplate* SingleEquipmentConfigPlugin::CreateDocTemplate()
{
	CDTMultiDocTemplate* pAddDocTmpl = new CDTMultiDocTemplate(
		ConfigurationPluginDLL.hResource,
		IDR_SINGLEEQUIPMEN_CFG,
		RUNTIME_CLASS(SingleEquipmentConfigDoc),
		RUNTIME_CLASS(SingleEquipmentConfigChildWnd),
		RUNTIME_CLASS(SingleEquipmentConfigView),
		this);

	return pAddDocTmpl;
}

void SingleEquipmentConfigPlugin::OnOpenSingleCfg()
{
	ASSERT(NULL != m_pDocTemplate);
	if(NULL == m_pDocTemplate)
	{
		return;
	}

	CString newDocName = GetCreateDocumentName();

	CDocument* matchedDocument = GetDocument(newDocName);
	
	if(NULL != matchedDocument)
	{
		POSITION viewPos = matchedDocument->GetFirstViewPosition();
		while(NULL != viewPos)
		{
			CView* documentView = matchedDocument->GetNextView(viewPos);
			documentView->GetParentFrame()->BringWindowToTop();
		}

		return;
	}

	/*相应文档不存在，进行创建*/
	AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, NULL, NULL);
}

void SingleEquipmentConfigPlugin::OnUpdateOpenSingleCfgUI(CCmdUI* pCmdUI)
{
	if(NULL != NetElementViewModelManager::GetInstance()->GetSelectedNetElement())
	{
		pCmdUI->Enable(TRUE);

		return;
	}

	pCmdUI->Enable(FALSE);
	return;
}

CString SingleEquipmentConfigPlugin::GetCreateDocumentName()
{
	return ConfigDocumentNameUtil::CreateSingleEquipmentConfigDocumentName();
}

CDocument* SingleEquipmentConfigPlugin::GetDocument(const CString& documentName)
{
	CDocument* matchedDocument = NULL;

	POSITION curDocumentPos = m_pDocTemplate->GetFirstDocPosition();
	while(curDocumentPos)
	{
		CDocument* curDocument = m_pDocTemplate->GetNextDoc(curDocumentPos);

		if(0 != documentName.CompareNoCase(curDocument->GetTitle()))
			continue;

		matchedDocument = curDocument;
		break;
	}

	return matchedDocument;
}

BOOL SingleEquipmentConfigPlugin::LoadDefaultToolBarEx(CMFCToolBar* pLoadToolBar)
{
	return FALSE;
}

BOOL SingleEquipmentConfigPlugin::LoadDocumentToolBarEx(CMFCToolBar* pLoadToolBar)
{
	return FALSE;
}

CString SingleEquipmentConfigPlugin::GetDefaultToolBarTitle()
{
	return "单站配置";
}

CString SingleEquipmentConfigPlugin::GetDocumentToolBarTitle()
{
	return "";
}

BOOL SingleEquipmentConfigPlugin::HasDefaultToolBar()
{
	return FALSE;
}

BOOL SingleEquipmentConfigPlugin::HasDocumentToolBar()
{
	return FALSE;
}

