//===========================================================================//
//  FILE:  OperationParameterDialog.h											//
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
#pragma once
#include "BCGCBPro/BCGCBProInc.h"
#include <vector>
#include "OperationParameter.h"

using std::vector;

// OperationParameterDialog 对话框
class OperationParameterDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OperationParameterDialog)

protected:
	/*要显示的命令*/
	IMibCommand& curCommand;

	/*用户输入的参数*/
	vector<OperationParameterPtr>* userInputParameters;

	/*参数输入Grid*/
	CBCGPGridCtrl parameterInputCtrl;

	/*参数设置控件的占位控件，用于创建时获得位置大小*/
	CStatic parameterConfigArea;

	CButton btnOK;

	static int PARAMETER_NAME_COLUMN_INDEX;

	static int PARAMETER_VALUE_COLUMN_INDEX;

	static int PARAMETER_RANGE_COLUMN_INDEX;

	static int PARAMETER_UNIT_COLUNM_INDEX;

public:
	OperationParameterDialog(IMibCommand& command, vector<OperationParameterPtr>*  inputParameters, CWnd* pParent = NULL);   // 标准构造函数

	virtual ~OperationParameterDialog();

// 对话框数据
	enum { IDD = IDD_OPERATION_PARAMETER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void SetPromptTitle();

	BOOL CreateParameterGrid();

	BOOL FillParameterGrid();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual BOOL OnInitDialog();
};
