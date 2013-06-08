//===========================================================================//
//  FILE:  EnumOperationParameter.cpp											//
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
#include "StdAfx.h"
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <string>
#include "EnumOperationParameter.h"

using std::string;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

EnumOperationParameter::EnumOperationParameter()
	: OperationParameter()
{
}

EnumOperationParameter::EnumOperationParameter(IMibNode* mibNode, const CString& parameterValue)
	: OperationParameter(mibNode, parameterValue)
{
}

EnumOperationParameter::~EnumOperationParameter(void)
{
}

void EnumOperationParameter::Initialize(IMibNode* mibNode, const CString& value)
{
	OperationParameter::Initialize(mibNode, value);

	ParseValueRange();
}

void EnumOperationParameter::ParseValueRange()
{
	string valueRange = GetValueRange();

	//对形如："1:创建/2:删除...."的文本进行拆分成取值段
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sectionSeparator("/");
	tokenizer valueSection(valueRange, sectionSeparator);

	for (tokenizer::iterator sectionIterator = valueSection.begin(); sectionIterator != valueSection.end(); ++sectionIterator)
	{
		boost::char_separator<char> valueSeparator(":");
		tokenizer valueAndDescription(*sectionIterator, valueSeparator);

		tokenizer::iterator valueIterator = valueAndDescription.begin();

		if(valueAndDescription.end() == valueIterator)
			continue;

		string curValue = *valueIterator;

		++valueIterator;
		if(valueAndDescription.end() == valueIterator)
			continue;

		string curDescription = *valueIterator;

		AddValueSection(curValue.c_str(), curDescription.c_str());
	}
}

void EnumOperationParameter::AddValueSection(const CString& value, const CString& description)
{
	ValuePair addValue;
	addValue.value = value;
	addValue.description = description;

	valueSections.push_back(addValue);
}

BOOL EnumOperationParameter::GetValueSections(vector<boost::any>& valueSectionCopy)
{
	BOOST_FOREACH(ValuePair valueSegment, valueSections)
	{
		valueSectionCopy.push_back(valueSegment);
	}

	return TRUE;
}

CString EnumOperationParameter::GetDisplayValue()
{
	return GetValueDescription(GetValue());
}

CString EnumOperationParameter::GetValueDescription(const CString& value)
{
	BOOST_FOREACH(ValuePair valueSegment, valueSections)
	{
		if( 0 != valueSegment.value.CompareNoCase(value))
			continue;

		return valueSegment.description;
	}

	return "null";
}
