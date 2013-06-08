//===========================================================================//
//  FILE:  OperationParameterFactory.h											//
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

#pragma once

#include <boost/function.hpp>
#include <map>
#include "DTUtilityInc/DTSingleton.h"
#include "OperationParameter.h"

using std::map;

class IMibNode;

class OperationParameterFactory
{
	DECLARE_SINGLETON_HASINIT(OperationParameterFactory)

protected:
	void Init();

	void UnInit();

public:
	OperationParameterPtr CreateOperationParameter(IMibNode* mibNode,  const CString& value);

protected:
	/*创建GridItem的函数对象声明*/
	typedef boost::function<OperationParameterPtr (IMibNode*, const CString&)> CreateOperationParameterFunctor;

	CreateOperationParameterFunctor FindCreateFunctor(const CString& findKey);

	OperationParameterPtr CreateEnumParameter(IMibNode* mibNode, const CString& value);

	OperationParameterPtr CreateDefaultParameter(IMibNode* mibNode, const CString& value);

	bool IfFunctorKeyMatched(std::pair<CString, CreateOperationParameterFunctor> curIterator, const CString& matchedKey);

private:
	/*存放创建各种OperationParameter的仿函数*/
	map<CString, CreateOperationParameterFunctor> createOperationParameterFunctors;

	CString DEFAULTTYPE;
};

