//===========================================================================//
//  FILE:  ConfigObjectViewModel.h											//
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
#pragma once

class CObjInfo;

class ConfigObjectViewModel
{
protected:
	ConfigObjectViewModel();

public:
	ConfigObjectViewModel(CObjInfo* hostConfigObject);

	virtual ~ConfigObjectViewModel(void);

public:
	CString GetName();

	BOOL HasChildNode();

	BOOL IsChildNodeLoaded();

	void SetChildNodeIsLoadedFlag(BOOL isLoaded);

	CObjInfo* GetDataModel();

protected:
	void Initialize(CObjInfo* hostConfigObject, BOOL isLoadedChildNode);

private:
	CObjInfo* configObject;

	BOOL isChildNodeLoaded;
};

