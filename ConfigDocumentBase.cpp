// ConfigDocumentBase.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigObjectViewModel.h"
#include "ConfigDocumentBase.h"
#include "templatedef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ConfigDocumentBase

IMPLEMENT_DYNCREATE(ConfigDocumentBase, CDocument)

ConfigDocumentBase::ConfigDocumentBase()
: configInfoVersionNo("")
, selectedConfigObjectViewModel(NULL)
{
}

BOOL ConfigDocumentBase::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

ConfigDocumentBase::~ConfigDocumentBase()
{
	ClearCollection(configObjectViewModels);
}


BEGIN_MESSAGE_MAP(ConfigDocumentBase, CDocument)
END_MESSAGE_MAP()


// ConfigDocumentBase diagnostics

#ifdef _DEBUG
void ConfigDocumentBase::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void ConfigDocumentBase::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// ConfigDocumentBase serialization

void ConfigDocumentBase::Serialize(CArchive& ar)
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

CString ConfigDocumentBase::GetConfigInfoVersionNo()
{
	return configInfoVersionNo;
}

void ConfigDocumentBase::SetConfigInfoVersionNo(const CString& versionNo)
{
	configInfoVersionNo = versionNo;
}

void ConfigDocumentBase::AddConfigObjectViewModel(ConfigObjectViewModel* addViewModel)
{
	if(NULL == addViewModel)
		return;

	configObjectViewModels.push_back(addViewModel);
}

void ConfigDocumentBase::SetSelectedConfigObjectViewModel(ConfigObjectViewModel* selectedCfgObjViewModel)
{
	this->selectedConfigObjectViewModel = selectedCfgObjViewModel;
}

ConfigObjectViewModel* ConfigDocumentBase::GetSelectedConfigObjectViewModel()
{
	return selectedConfigObjectViewModel;
}
