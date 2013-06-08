//===========================================================================//
//  FILE:  OperationParameterFactory.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   �������������ࡣ												//
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
	/*����GridItem�ĺ�����������*/
	typedef boost::function<OperationParameterPtr (IMibNode*, const CString&)> CreateOperationParameterFunctor;

	CreateOperationParameterFunctor FindCreateFunctor(const CString& findKey);

	OperationParameterPtr CreateEnumParameter(IMibNode* mibNode, const CString& value);

	OperationParameterPtr CreateDefaultParameter(IMibNode* mibNode, const CString& value);

	bool IfFunctorKeyMatched(std::pair<CString, CreateOperationParameterFunctor> curIterator, const CString& matchedKey);

private:
	/*��Ŵ�������OperationParameter�ķº���*/
	map<CString, CreateOperationParameterFunctor> createOperationParameterFunctors;

	CString DEFAULTTYPE;
};

