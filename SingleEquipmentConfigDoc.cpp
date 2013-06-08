// SingleEquipmentConfigDoc.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "NetElementViewModelInc/NetElementViewModelExport.h"
#include "SingleEquipmentConfigDoc.h"
#include "ConfigDocumentNameUtil.h"
#include "ConfigObjectViewModel.h"
#include "SingleEquipmentConfigView.h"
#include "WaitDialog.h"
#include "ConfigObjectOperationTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// SingleEquipmentConfigDoc

IMPLEMENT_DYNCREATE(SingleEquipmentConfigDoc, ConfigDocumentBase)

SingleEquipmentConfigDoc::SingleEquipmentConfigDoc()
: hostNetElementViewModel(NULL)	
, getInstancePtr(NULL)
, instanceTablePtr(NULL)
, waitWindow(NULL)
{
}

BOOL SingleEquipmentConfigDoc::OnNewDocument()
{
	if (!ConfigDocumentBase::OnNewDocument())
		return FALSE;

	CString documentName = ConfigDocumentNameUtil::CreateSingleEquipmentConfigDocumentName();

	SetTitle(documentName);

	hostNetElementViewModel = NetElementViewModelManager::GetInstance()->GetSelectedNetElement();
	if(NULL == hostNetElementViewModel)
	{
		return FALSE;
	}

	SetConfigInfoVersionNo(hostNetElementViewModel->GetMibVersionNo());

	return TRUE;
}

SingleEquipmentConfigDoc::~SingleEquipmentConfigDoc()
{
}


BEGIN_MESSAGE_MAP(SingleEquipmentConfigDoc, ConfigDocumentBase)
END_MESSAGE_MAP()


// SingleEquipmentConfigDoc diagnostics

#ifdef _DEBUG
void SingleEquipmentConfigDoc::AssertValid() const
{
	ConfigDocumentBase::AssertValid();
}

#ifndef _WIN32_WCE
void SingleEquipmentConfigDoc::Dump(CDumpContext& dc) const
{
	ConfigDocumentBase::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// SingleEquipmentConfigDoc serialization

void SingleEquipmentConfigDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif

void SingleEquipmentConfigDoc::SetSelectedConfigObjectViewModel(ConfigObjectViewModel* selectedCfgObjViewModel)
{
	ConfigDocumentBase::SetSelectedConfigObjectViewModel(selectedCfgObjViewModel);

	if(NULL == selectedCfgObjViewModel)
	{
		return;
	}

	if(NULL == hostNetElementViewModel)
	{
		return;
	}

	UpdateOperationView(selectedCfgObjViewModel);

	WaitDialog waitDlg;
	waitWindow = &waitDlg;
	
	CObjInfo* hostObjectInfo = selectedCfgObjViewModel->GetDataModel();

	/*返回的句柄用于取消查询过程*/
	getInstancePtr = hostNetElementViewModel->BeginGetObjectInstance(hostObjectInfo->GetMibTabName(), boost::bind(&SingleEquipmentConfigDoc::GetInstanceCallBack, this, _1));

	INT_PTR retCode = waitDlg.DoModal();

	waitWindow = NULL;
	if(IDOK == retCode)
	{
		/*用户取消查询*/
		hostNetElementViewModel->StopGetObjectInstance(getInstancePtr);
	}
}

void SingleEquipmentConfigDoc::GetInstanceCallBack(IMibInstanceTablePtr mibIntanceTable)
{
	SetInstanceTable(mibIntanceTable);

	CloseWaitWindows();
}

void SingleEquipmentConfigDoc::SetInstanceTable(IMibInstanceTablePtr mibInstanceTable)
{
	instanceTablePtr = mibInstanceTable;

	UpdateInstancesViews(instanceTablePtr);
}

void SingleEquipmentConfigDoc::UpdateInstancesViews(IMibInstanceTablePtr mibInstanceTable)
{
	POSITION viewPosition = GetFirstViewPosition();
	while (viewPosition != NULL)
	{
		CView* dataView = GetNextView(viewPosition);
		SingleEquipmentConfigView* singleCfgView = DYNAMIC_DOWNCAST(SingleEquipmentConfigView, dataView);

		if(NULL == singleCfgView)
			continue;

		singleCfgView->UpdateView(mibInstanceTable);
	}	
}

void SingleEquipmentConfigDoc::UpdateOperationView(ConfigObjectViewModel* selectedCfgObjViewModel)
{
	POSITION viewPosition = GetFirstViewPosition();
	while (viewPosition != NULL)
	{
		CView* dataView = GetNextView(viewPosition);
		ConfigObjectOperationTreeView* operationTreeView = DYNAMIC_DOWNCAST(ConfigObjectOperationTreeView, dataView);

		if(NULL == operationTreeView)
			continue;

		operationTreeView->UpdateView(selectedCfgObjViewModel);
		return;
	}	
}

void SingleEquipmentConfigDoc::CloseWaitWindows()
{
	if(NULL == waitWindow || !(::IsWindow(waitWindow->m_hWnd)))
		return;

	SendMessage(waitWindow->m_hWnd, WM_CLOSE, 0, 0);
}
