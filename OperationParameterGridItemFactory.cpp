//===========================================================================//
//  FILE:  OperationParameterGridItemFactory.cpp										//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   显示命令参数的GridItem工厂类。												//
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
//	 2013-06-07 - create by pengqiang										//
//==========================================================================//
#include "StdAfx.h"
#include "OperationParameterGridItemFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SINGLETON(OperationParameterGridItemFactory)

void OperationParameterGridItemFactory::Init()
{
	createGridItemFunctions.insert(std::make_pair("INTEGER", boost::bind<CBCGPGridItem*>(&OperationParameterGridItemFactory::CreateComboboxGridItem, this, _1)));

	createGridItemFunctions.insert(std::make_pair("RowStatus", boost::bind<CBCGPGridItem*>(&OperationParameterGridItemFactory::CreateComboboxGridItem, this, _1)));

	createGridItemFunctions.insert(std::make_pair("InetAddressType", boost::bind<CBCGPGridItem*>(&OperationParameterGridItemFactory::CreateComboboxGridItem, this, _1)));
}

void OperationParameterGridItemFactory::UnInit()
{
}

CBCGPGridItem* OperationParameterGridItemFactory::CreateGridItem(OperationParameterPtr operationParamPtr)
{
	if(NULL == operationParamPtr)
	{
		return NULL;
	}

	CreateGridItemFunctor createGridItemFunctor = FindCreateGridItemFunctor(operationParamPtr->GetDisplayType());
	if(createGridItemFunctor.empty())
	{
		//TODO Load default
	}

	return createGridItemFunctor(operationParamPtr);
}

CBCGPGridItem* OperationParameterGridItemFactory::CreateComboboxGridItem(OperationParameterPtr parameterPtr)
{
	

	return NULL;
}

OperationParameterGridItemFactory::CreateGridItemFunctor OperationParameterGridItemFactory::FindCreateGridItemFunctor(const CString& findKey)
{
	std::map<CString, CreateGridItemFunctor, NoCaseSensitiveLessCompareFunctor>::const_iterator findIterator = 
		std::find_if(createGridItemFunctions.begin(), createGridItemFunctions.end(), 
						  boost::bind<bool>(&OperationParameterGridItemFactory::IfKeyMatched, this, _1, findKey));

	if(findIterator != createGridItemFunctions.end())
	{
		return findIterator->second;
	}

	return NULL;
}

bool OperationParameterGridItemFactory::IfKeyMatched(std::pair<CString, CreateGridItemFunctor> curIterator, const CString& matchedKey)
{
	CString curKey = curIterator.first;

	if( 0 == matchedKey.CompareNoCase(curKey))
	{
		return true;
	}

	return false;
}
