//===========================================================================//
//  FILE:  ConfigObjectTreeLoader.h											//
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
#pragma once

class ConfigDocumentBase;

class CObjInfo;

class ConfigObjectTreeLoader
{
protected:
	ConfigObjectTreeLoader(void);

public:
	virtual ~ConfigObjectTreeLoader(void);

public:
	static int CONFIG_OBJECT_ROOT_IMG_INDEX;

	static int CONFIG_OBJECT_LEAF_IMG_INDEX;

	static int CONFIG_OBJECT_FOLDER_IMG_INDEX;

public:
	static void LoadRootNode(ConfigDocumentBase* configDocument, CTreeCtrl* targetTreeControl);

	static void LoadChildNode(ConfigDocumentBase* configDocument, CTreeCtrl* targetTreeControl, HTREEITEM parentTreeItem);

private:
	static void LoadChildNode(ConfigDocumentBase* configDocument, class CObjInfo* parentObjectModel, CTreeCtrl* targetTreeControl, HTREEITEM parentTreeItem);

	static void RemoveChildNode(CTreeCtrl* targetTreeControl, HTREEITEM parentTreeItem);

	static void SetObjectNodeNameBold(CObjInfo* objectInfo, HTREEITEM objTreeItem, CTreeCtrl* hostTreeControl);

	static int GetNodeImageIndex(CObjInfo* objectInfo);
};

