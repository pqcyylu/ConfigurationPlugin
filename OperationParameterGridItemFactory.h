//===========================================================================//
//  FILE:  OperationParameterGridItemFactory.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   ��ʾ���������GridItem�����ࡣ												//
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
#include <boost/ref.hpp>
#include <map>
#include "BCGCBPro/BCGCBProInc.h"
#include "DTUtilityInc/DTSingleton.h"
#include "DTUtilityInc/DTUtilityInc.h"
#include "OperationParameter.h"

using std::map;

class OperationParameterGridItemFactory
{
	DECLARE_SINGLETON_HASINIT(OperationParameterGridItemFactory)

private:
	/*����GridItem�ĺ�����������*/
	typedef boost::function<CBCGPGridItem* (OperationParameterPtr)> CreateGridItemFunctor;

	map<CString, CreateGridItemFunctor, NoCaseSensitiveLessCompareFunctor> createGridItemFunctions;

public:
	CBCGPGridItem* CreateGridItem(OperationParameterPtr operationParamPtr);

protected:
	void Init();

	void UnInit();

	CBCGPGridItem* CreateComboboxGridItem(OperationParameterPtr operationParameter);

	CBCGPGridItem* CreateDefaultGridItem(OperationParameterPtr operationParameter);

	CreateGridItemFunctor FindCreateGridItemFunctor(const CString& findKey);

	bool IfKeyMatched(std::pair<CString, CreateGridItemFunctor> curIterator, const CString& matchedKey);
};

