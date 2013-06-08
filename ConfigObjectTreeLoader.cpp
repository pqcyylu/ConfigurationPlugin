//===========================================================================//
//  FILE:  ConfigObjectTreeLoader.cpp											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	网元配置对象的加载器。													//
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

//加载网元的信息模型树，采用延迟加载的策略用于提高效率，防止主界面阻塞，只加载根节点的子节点，孙子节点等到用户点击相应父节点时才加载和展开
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
		errorCause.Format("为网元%s加载对象模型树时出错，传入的树形控件:targetTreeControl为空",configDocument->GetTitle());
		L_ERROR(errorCause);

		return;
	}
	
	/*添加第一层的节点*/
	IInfoObjectDepository* infoObjDepository = CDTMemDBInfoMgr::GetInstance()->GetInfoObjectDepository();
	if(NULL == infoObjDepository)
	{
		L_ERROR("IInfoObjectDepoistory信息模型管理库为空！");

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
		errorCause.Format("加载子对象模型出错，树控件targetTreeControl为空!");

		L_ERROR(errorCause);
		return;
	}

	if(NULL == parentTreeItem)
	{
		errorCause.Format("加载子对象模型出错，父节点parentTreeItem为空!");

		L_ERROR(errorCause);
		return;
	}

	ConfigObjectViewModel *configObjectViewModel = (ConfigObjectViewModel*)(targetTreeControl->GetItemData(parentTreeItem));
	if(NULL == configObjectViewModel)
	{
		errorCause = "网元的节点数据configObjectViewModel为空，无法子节点对象！";

		L_ERROR(errorCause);
		return;
	}

	/*已加载过子节点*/
	if(configObjectViewModel->IsChildNodeLoaded())
	{
		return;
	}

	//移除之前占位的LazyNode
	RemoveChildNode(targetTreeControl, parentTreeItem);

	//加载实际的ChildNode
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
		errorCause.Format("加载子对象模型出错，父对象parentObjectModel为空!");

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

		//如果该子节点有子节点，加载一个lazyNode进行占位
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
		L_ERROR("传入的objectInfo为空，无法设置对象名粗体显示");
		return;
	}

	if(NULL == objTreeItem)
	{
		L_ERROR("传入的objTreeItem为空，无法设置对象名粗体显示");
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


