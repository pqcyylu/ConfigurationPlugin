//===========================================================================//
//  FILE:  EnumOperationParameter.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   枚举型的参数。												//
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
//	 2013-06-05 - create by pengqiang										//
//==========================================================================//
#pragma once

#include "OperationParameter.h"

class EnumOperationParameter : public OperationParameter
{
protected:
	EnumOperationParameter(void);

public:
	EnumOperationParameter(IMibNode* mibNode, const CString& parameterValue);

	virtual ~EnumOperationParameter(void);

	struct  ValuePair
	{
		CString value;
		CString description;
	};

public:
	virtual CString GetDisplayValue();

	virtual BOOL GetValueSections(vector<boost::any>& valueSection);

protected:
	virtual void Initialize(IMibNode* mibNode, const CString& value);

	void ParseValueRange();

	void AddValueSection(const CString& value, const CString& description);

	CString GetValueDescription(const CString& value);

private:
	/*取值集合*/
	vector<ValuePair> valueSections; 
};

