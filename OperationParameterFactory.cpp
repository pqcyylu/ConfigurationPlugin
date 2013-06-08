//===========================================================================//
//  FILE:  OperationParameterFactory.cpp											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   操作参数工厂类。												//
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
#include <boost/make_shared.hpp>
#include "NetElementModelInc/NetElementModelExport.h"
#include "OperationParameterFactory.h"
#include "EnumOperationParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SINGLETON(OperationParameterFactory)

void OperationParameterFactory::Init()
{
	DEFAULTTYPE = "default";

	createOperationParameterFunctors.insert(std::make_pair("INTEGER", boost::bind<OperationParameterPtr>(&OperationParameterFactory::CreateEnumParameter, this, _1, _2)));

	createOperationParameterFunctors.insert(std::make_pair("RowStatus", boost::bind<OperationParameterPtr>(&OperationParameterFactory::CreateEnumParameter, this, _1, _2)));

	createOperationParameterFunctors.insert(std::make_pair("InetAddressType", boost::bind<OperationParameterPtr>(&OperationParameterFactory::CreateEnumParameter, this, _1, _2)));

	createOperationParameterFunctors.insert(std::make_pair(DEFAULTTYPE, boost::bind<OperationParameterPtr>(&OperationParameterFactory::CreateDefaultParameter, this, _1, _2)));
}

void OperationParameterFactory::UnInit()
{
}

OperationParameterPtr OperationParameterFactory::CreateOperationParameter(IMibNode* mibNode, const CString& value)
{
	CreateOperationParameterFunctor createFunctor = FindCreateFunctor(mibNode->GetAsnType());

	if(createFunctor.empty())
	{
		createFunctor = FindCreateFunctor(DEFAULTTYPE);
		ASSERT(!createFunctor.empty());

		if(createFunctor.empty())
		{
			return NULL;
		}
	}

	return createFunctor(mibNode, value);
}

OperationParameterFactory::CreateOperationParameterFunctor OperationParameterFactory::FindCreateFunctor(const CString& findKey)
{
	std::map<CString, CreateOperationParameterFunctor>::const_iterator findIterator = 
		std::find_if(createOperationParameterFunctors.begin(), createOperationParameterFunctors.end(), 
		boost::bind<bool>(&OperationParameterFactory::IfFunctorKeyMatched, this, _1, findKey));

	if(findIterator != createOperationParameterFunctors.end())
	{
		return findIterator->second;
	}

	return NULL;
}

OperationParameterPtr OperationParameterFactory::CreateEnumParameter(IMibNode* mibNode, const CString& value)
{
	return boost::make_shared<EnumOperationParameter>(mibNode, value);
}

OperationParameterPtr OperationParameterFactory::CreateDefaultParameter(IMibNode* mibNode, const CString& value)
{
	return boost::make_shared<OperationParameter>(mibNode, value);
}

bool OperationParameterFactory::IfFunctorKeyMatched(std::pair<CString, CreateOperationParameterFunctor> curIterator, const CString& matchedKey)
{
	CString curFunctorKey = curIterator.first;

	if( 0 == matchedKey.CompareNoCase(curFunctorKey))
	{
		return true;
	}

	return false;
}

