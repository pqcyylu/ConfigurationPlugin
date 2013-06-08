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
#include "StdAfx.h"
#include "OperationParameter.h"
#include "NetElementModelInc/NetElementModelExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

OperationParameter::OperationParameter(void)
{
	Initialize(NULL, "");
}

OperationParameter::OperationParameter(IMibNode* mibNode, const CString& parameterValue)
{
	Initialize(mibNode, parameterValue);
}

OperationParameter::~OperationParameter(void)
{
}

void OperationParameter::Initialize(IMibNode* mibNode, const CString& value)
{
	this->mibNode = mibNode;

	this->valueContent =  value;
}

CString OperationParameter::GetDisplayName()
{
	if(mibNode == NULL)
		return "";

	return mibNode->GetFriendName();
}

CString OperationParameter::GetValue()
{
	return valueContent;
}

void OperationParameter::SetValue(const CString& value)
{
	valueContent = value;
}

CString OperationParameter::GetDisplayValue()
{
	return valueContent;
}

CString OperationParameter::GetValueRange()
{
	if(mibNode == NULL)
		return "";

	return mibNode->GetMibValueList();
}

CString OperationParameter::GetValueUnit()
{
	if(mibNode == NULL)
		return "";

	return mibNode->GetUnit();
}

CString OperationParameter::GetDisplayType()
{
	if(NULL == mibNode)
		return "";

	return mibNode->GetAsnType();
}

BOOL OperationParameter::GetValueSections(vector<boost::any>& valueSection)
{
	return FALSE;
}


