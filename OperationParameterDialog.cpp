//===========================================================================//
//  FILE:  OperationParameterDialog.cpp											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   参数设置对话框。												//
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
//	 2013-06-04 - create by pengqiang										//
//==========================================================================//
#include "stdafx.h"
#include "resource.h"
#include "afxdialogex.h"
#include "boost/foreach.hpp"
#include "NetElementModelInc/NetElementModelExport.h"
#include "ConfigObjectViewModel.h"
#include "OperationParameterDialog.h"

#define IDC_INPUTPARAMETER_GRID_CTRL_ID 1

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int OperationParameterDialog::PARAMETER_NAME_COLUMN_INDEX = 0;

int OperationParameterDialog::PARAMETER_VALUE_COLUMN_INDEX = 1;

int OperationParameterDialog::PARAMETER_RANGE_COLUMN_INDEX = 2;

int OperationParameterDialog::PARAMETER_UNIT_COLUNM_INDEX = 3;

// OperationParameterDialog 对话框
IMPLEMENT_DYNAMIC(OperationParameterDialog, CDialogEx)

OperationParameterDialog::OperationParameterDialog(IMibCommand& command,  vector<OperationParameterPtr>*  inputParameters, CWnd* pParent /*=NULL*/)
	: CDialogEx(OperationParameterDialog::IDD, pParent)
	,  curCommand(command)
	,  userInputParameters(inputParameters)
{
}

OperationParameterDialog::~OperationParameterDialog()
{
}

void OperationParameterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, btnOK);
	DDX_Control(pDX, IDC_STATIC_PARAMETERGRID_AREA, parameterConfigArea);
}

BEGIN_MESSAGE_MAP(OperationParameterDialog, CDialogEx)
END_MESSAGE_MAP()

void OperationParameterDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//AdjustLayout();
}

BOOL OperationParameterDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetPromptTitle();

	if(!CreateParameterGrid())
	{
		return FALSE;
	}

	if(!FillParameterGrid())
	{
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void OperationParameterDialog::SetPromptTitle()
{
	SetWindowText(curCommand.GetDisplayName());
}

BOOL OperationParameterDialog::CreateParameterGrid()
{
	CRect rectParameterInputRect;
	parameterConfigArea.GetClientRect(&rectParameterInputRect);
	parameterConfigArea.MapWindowPoints(this, &rectParameterInputRect);

	if(!parameterInputCtrl.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectParameterInputRect, this, IDC_INPUTPARAMETER_GRID_CTRL_ID))
	{
		return FALSE;
	}

	/*禁止排序*/
	parameterInputCtrl.EnableMarkSortedColumn (FALSE);

	CString parameterName;
	if(!parameterName.LoadString(IDS_OPERATION_PARAMETER_NAME))
	{
		parameterName = "参数名";
	}
	parameterInputCtrl.InsertColumn(PARAMETER_NAME_COLUMN_INDEX, parameterName, 100);

	CString parameterValue;
	if(!parameterValue.LoadString(IDS_OPERATION_PARAMETER_VALUE))
	{
		parameterValue = "参数值";
	}
	parameterInputCtrl.InsertColumn(PARAMETER_VALUE_COLUMN_INDEX, parameterValue, 100);

	CString parameterRange;
	if(!parameterRange.LoadString(IDS_OPERATION_PARAMETER_VALRANGE))
	{
		parameterRange = "取值范围";
	}
	parameterInputCtrl.InsertColumn(PARAMETER_RANGE_COLUMN_INDEX, parameterRange, 100);

	CString parameterUnit;
	if(!parameterUnit.LoadString(IDS_OPERATION_PARAMETER_VALUNIT))
	{
		parameterUnit = "取值单位";
	}
	parameterInputCtrl.InsertColumn(PARAMETER_UNIT_COLUNM_INDEX, parameterUnit, 100);

	return TRUE;
}

BOOL OperationParameterDialog::FillParameterGrid()
{
	if(NULL == userInputParameters)
		return FALSE;

	vector<OperationParameterPtr>::const_iterator curIterator = userInputParameters->begin();
	vector<OperationParameterPtr>::const_iterator endPos = userInputParameters->end();
	for(; curIterator != endPos; curIterator++)
	{
		OperationParameterPtr curParameterPtr = *curIterator;
		CBCGPGridRow* parameterRow = parameterInputCtrl.CreateRow(parameterInputCtrl.GetColumnCount());

		CBCGPGridItem* nameGridItem = parameterRow->GetItem(PARAMETER_NAME_COLUMN_INDEX);
		nameGridItem->SetValue((LPCSTR)curParameterPtr->GetDisplayName(), FALSE);
		nameGridItem->AllowEdit(FALSE);

		CBCGPGridItem* valueGridItem = parameterRow->GetItem(PARAMETER_VALUE_COLUMN_INDEX);
		valueGridItem->SetValue((LPCSTR)curParameterPtr->GetValue(), FALSE);

		CBCGPGridItem* rangeGridItem = parameterRow->GetItem(PARAMETER_RANGE_COLUMN_INDEX);
		rangeGridItem->SetValue((LPCSTR)curParameterPtr->GetValueRange(), FALSE);
		rangeGridItem->AllowEdit(FALSE);

		CBCGPGridItem* unitGridItem = parameterRow->GetItem(PARAMETER_UNIT_COLUNM_INDEX);
		unitGridItem->SetValue((LPCSTR)curParameterPtr->GetValueUnit(), FALSE);
		unitGridItem->AllowEdit(FALSE);

		parameterInputCtrl.AddRow(parameterRow, FALSE);

		parameterRow->SetData((DWORD_PTR)curParameterPtr.get());
	}

	parameterInputCtrl.AdjustLayout();

	return TRUE;
}