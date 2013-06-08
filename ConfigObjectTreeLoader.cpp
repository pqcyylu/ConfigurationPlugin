//===========================================================================//
//  FILE:  ConfigObjectTreeLoader.cpp											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	��Ԫ���ö���ļ�������													//
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
//	 2013-05-17 - create by pengqiang										//
//==========================================================================//
#include "StdAfx.h"
#include "resource.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "ConfigDocumentBase.h"
#include "ConfigObjectViewModel.h"
#include "ConfigObjectTreeLoader.h"
#include "AveLogMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int ConfigObjectTreeLoader::CONFIG_OBJECT_ROOT_IMG_INDEX = 1;

int ConfigObjectTreeLoader::CONFIG_OBJECT_FOLDER_IMG_INDEX = 2;

int ConfigObjectTreeLoader::CONFIG_OBJECT_LEAF_IMG_INDEX = 3;

ConfigObjectTreeLoader::ConfigObjectTreeLoader(void)
{
}


ConfigObjectTreeLoader::~ConfigObjectTreeLoader(void)
{
}

//������Ԫ����Ϣģ�����������ӳټ��صĲ����������Ч�ʣ���ֹ������������ֻ���ظ��ڵ���ӽڵ㣬���ӽڵ�ȵ��û������Ӧ���ڵ�ʱ�ż��غ�չ��
void ConfigObjectTreeLoader::LoadRootNode(ConfigDocumentBase* configDocument, CTreeCtrl* targetTreeControl)
{
	L_AUTRACE(1);

	if(NULL == configDocument)
	{
		return;
	}

	if(NULL == targetTreeControl)
	{
		CString errorCause;
		errorCause.Format("Ϊ��Ԫ%s���ض���ģ����ʱ������������οؼ�:targetTreeControlΪ��",configDocument->GetTitle());
		L_ERROR(errorCause);

		return;
	}
	
	/*��ӵ�һ��Ľڵ�*/
	IInfoObjectDepository* infoObjDepository = CDTMemDBInfoMgr::GetInstance()->GetInfoObjectDepository();
	if(NULL == infoObjDepository)
	{
		L_ERROR("IInfoObjectDepoistory��Ϣģ�͹����Ϊ�գ�");

		return;
	}

	const VECT_OBJINFO& vectRootObjs = infoObjDepository->GetRootObjVect(configDocument->GetConfigInfoVersionNo());

	VECT_OBJINFO::const_iterator iteratorCur = vectRootObjs.begin();
	VECT_OBJINFO::const_iterator endPos = vectRootObjs.end();
	for(; iteratorCur != endPos; iteratorCur++)
	{
		CObjInfo* configObject = *iteratorCur;
		if(NULL == configObject)
			continue;

		ConfigObjectViewModel* configObjectViewModel = new ConfigObjectViewModel(configObject);

		configDocument->AddConfigObjectViewModel(configObjectViewModel);

		int imageIndex = GetNodeImageIndex(configObject); 
	
		HTREEITEM configObjectUI = targetTreeControl->InsertItem(configObjectViewModel->GetName(), imageIndex, imageIndex);

		targetTreeControl->SetItemData(configObjectUI, (DWORD_PTR)configObjectViewModel);

		LoadChildNode(configDocument, configObject, targetTreeControl, configObjectUI);

		configObjectViewModel->SetChildNodeIsLoadedFlag(TRUE);

		targetTreeControl->Expand(configObjectUI, TVE_EXPAND);
	}

	targetTreeControl->Invalidate();
}

void ConfigObjectTreeLoader::LoadChildNode(ConfigDocumentBase* configDocument, CTreeCtrl* targetTreeControl, HTREEITEM parentTreeItem)
{
	L_AUTRACE(1);

	CString errorCause;

	if(NULL == targetTreeControl)
	{
		errorCause.Format("�����Ӷ���ģ�ͳ������ؼ�targetTreeControlΪ��!");

		L_ERROR(errorCause);
		return;
	}

	if(NULL == parentTreeItem)
	{
		errorCause.Format("�����Ӷ���ģ�ͳ������ڵ�parentTreeItemΪ��!");

		L_ERROR(errorCause);
		return;
	}

	ConfigObjectViewModel *configObjectViewModel = (ConfigObjectViewModel*)(targetTreeControl->GetItemData(parentTreeItem));
	if(NULL == configObjectViewModel)
	{
		errorCause = "��Ԫ�Ľڵ�����configObjectViewModelΪ�գ��޷��ӽڵ����";

		L_ERROR(errorCause);
		return;
	}

	/*�Ѽ��ع��ӽڵ�*/
	if(configObjectViewModel->IsChildNodeLoaded())
	{
		return;
	}

	//�Ƴ�֮ǰռλ��LazyNode
	RemoveChildNode(targetTreeControl, parentTreeItem);

	//����ʵ�ʵ�ChildNode
	CObjInfo* objectInfo = configObjectViewModel->GetDataModel();

	LoadChildNode(configDocument, objectInfo, targetTreeControl, parentTreeItem);

	configObjectViewModel->SetChildNodeIsLoadedFlag(TRUE);
}

void ConfigObjectTreeLoader::LoadChildNode(ConfigDocumentBase* configDocument, CObjInfo* parentObjectModel, CTreeCtrl* targetTreeControl, HTREEITEM parentTreeItem)
{
	L_AUTRACE(1);

	if(NULL == configDocument)
	{
		return;
	}

	CString errorCause;
	if(NULL == parentObjectModel)
	{
		errorCause.Format("�����Ӷ���ģ�ͳ���������parentObjectModelΪ��!");

		L_ERROR(errorCause);
		return;		
	}

	const VECT_OBJINFO& childObjects = parentObjectModel->GetChildObjVect();
	VECT_OBJINFO::const_iterator childItem = childObjects.begin();

	for(; childItem != childObjects.end(); childItem++)
	{
		CObjInfo* childObject = *childItem;
	
		ConfigObjectViewModel* childViewModel = new ConfigObjectViewModel(childObject);
		configDocument->AddConfigObjectViewModel(childViewModel);
	
		int nImage = GetNodeImageIndex(childObject);
		HTREEITEM hChild  = targetTreeControl->InsertItem(childViewModel->GetName(), nImage, nImage, parentTreeItem);
		targetTreeControl->SetItemData(hChild, (DWORD_PTR)childViewModel);

		//������ӽڵ����ӽڵ㣬����һ��lazyNode����ռλ
		if(childObject->IsHasChildren())
		{
			targetTreeControl->InsertItem("",0,0,hChild);
		}
	}

}

void ConfigObjectTreeLoader::SetObjectNodeNameBold(CObjInfo* objectInfo, HTREEITEM objTreeItem, CTreeCtrl* hostTreeControl)
{
	if(NULL == objectInfo)
	{
		L_ERROR("�����objectInfoΪ�գ��޷����ö�����������ʾ");
		return;
	}

	if(NULL == objTreeItem)
	{
		L_ERROR("�����objTreeItemΪ�գ��޷����ö�����������ʾ");
		return;
	}

	CString mibTableName = objectInfo->GetMibTabName();
	if(mibTableName.IsEmpty())
	{
		return;
	}

	//if(objectInfo->IsCanConfigure())
	//{
	//	hostTreeControl->SetItemBold(objTreeItem, TRUE);
	//}
}

void ConfigObjectTreeLoader::RemoveChildNode(CTreeCtrl* targetTreeControl, HTREEITEM parentTreeItem)
{
	HTREEITEM childItem = targetTreeControl->GetChildItem(parentTreeItem);
	while(NULL != childItem)
	{
		targetTreeControl->DeleteItem(childItem);

		childItem = targetTreeControl->GetChildItem(parentTreeItem);
	}
}

int ConfigObjectTreeLoader::GetNodeImageIndex(CObjInfo* objectInfo)
{
	if(NULL == objectInfo)
		return CONFIG_OBJECT_FOLDER_IMG_INDEX;

	if(!objectInfo->IsHasChildren() && !objectInfo->GetMibTabName().IsEmpty())
	{
		return CONFIG_OBJECT_LEAF_IMG_INDEX;
	}

	if(objectInfo->IsHasChildren() && !objectInfo->GetMibTabName().IsEmpty())
	{
		return CONFIG_OBJECT_ROOT_IMG_INDEX;
	}

	return CONFIG_OBJECT_FOLDER_IMG_INDEX;
}


