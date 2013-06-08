//===========================================================================//
//  FILE:  ConfigObjectViewModel.cpp											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	网元配置对象的ViewModel。												//
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
#include "ConfigObjectViewModel.h"
#include "NetElementModelInc/NetElementModelExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ConfigObjectViewModel::ConfigObjectViewModel(void)
	: configObject(NULL)
	, isChildNodeLoaded(FALSE)
{
}

ConfigObjectViewModel::ConfigObjectViewModel(CObjInfo* hostConfigObject)
	: configObject(hostConfigObject)
	, isChildNodeLoaded(FALSE)
{
}


ConfigObjectViewModel::~ConfigObjectViewModel(void)
{
}

CString ConfigObjectViewModel::GetName()
{
	if(NULL == configObject)
	{
		return "";
	}

	return configObject->GetObjName();
}

void ConfigObjectViewModel::Initialize(CObjInfo* hostConfigObject, BOOL isLoadedChildNode)
{
	configObject = hostConfigObject;

	isChildNodeLoaded = isLoadedChildNode;
}

BOOL ConfigObjectViewModel::HasChildNode()
{
	if(NULL == configObject)
	{
		return FALSE;
	}

	return configObject->IsHasChildren();
}

BOOL ConfigObjectViewModel::IsChildNodeLoaded()
{
	return isChildNodeLoaded;
}

void ConfigObjectViewModel::SetChildNodeIsLoadedFlag(BOOL isLoaded)
{
	isChildNodeLoaded = isLoaded;
}

CObjInfo* ConfigObjectViewModel::GetDataModel()
{
	return configObject;
}
