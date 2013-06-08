//===========================================================================//
//  FILE:  OperationParameter.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   ²Ù×÷²ÎÊý¡£												//
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

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

using std::vector;

class IMibNode;

class OperationParameter
{
protected:
	OperationParameter(void);

public:
	OperationParameter(IMibNode* mibNode, const CString& parameterValue);

	virtual ~OperationParameter(void);

public:
	CString GetDisplayName();

	CString GetValue();

	void SetValue(const CString& value);

	CString GetValueRange();

	CString GetValueUnit();

	CString GetDisplayType();

public:
	virtual CString GetDisplayValue();

	virtual BOOL GetValueSections(vector<boost::any>& valueSection);

protected:
	virtual void Initialize(IMibNode* mibNode, const CString& value);

private:
	IMibNode* mibNode;

	CString valueContent;
};

typedef boost::shared_ptr<OperationParameter> OperationParameterPtr;

