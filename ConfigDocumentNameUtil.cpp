#include "StdAfx.h"
#include "resource.h"
#include "ConfigDocumentNameUtil.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "NetElementViewModelInc/NetElementViewModelExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ConfigDocumentNameUtil::ConfigDocumentNameUtil(void)
{
}


ConfigDocumentNameUtil::~ConfigDocumentNameUtil(void)
{
}

CString ConfigDocumentNameUtil::CreateSingleEquipmentConfigDocumentName()
{
	NetElementViewModel* curSelectedNE = NetElementViewModelManager::GetInstance()->GetSelectedNetElement();
	if(NULL == curSelectedNE)
	{
		return "";
	}

	CString netElementName = curSelectedNE->GetName();

	CString newDocumentName;
	newDocumentName.LoadString(IDS_CONFIGURATION_TITLE);
	newDocumentName += "_" + netElementName;

	return newDocumentName;
}

CString ConfigDocumentNameUtil::CreateBatchConfigDocumentName()
{
	CString newDocumentName;
	newDocumentName.LoadString(IDS_BATCHCONFIG_TITLE);

	return newDocumentName;
}