//===========================================================================//
//  FILE:  OperationParameterDialog.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   �������öԻ���												//
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

// OperationParameterDialog �Ի���
class OperationParameterDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OperationParameterDialog)

protected:
	/*Ҫ��ʾ������*/
	IMibCommand& curCommand;

	/*�û�����Ĳ���*/
	vector<OperationParameterPtr>* userInputParameters;

	/*��������Grid*/
	CBCGPGridCtrl parameterInputCtrl;

	/*�������ÿؼ���ռλ�ؼ������ڴ���ʱ���λ�ô�С*/
	CStatic parameterConfigArea;

	CButton btnOK;

	static int PARAMETER_NAME_COLUMN_INDEX;

	static int PARAMETER_VALUE_COLUMN_INDEX;

	static int PARAMETER_RANGE_COLUMN_INDEX;

	static int PARAMETER_UNIT_COLUNM_INDEX;

public:
	OperationParameterDialog(IMibCommand& command, vector<OperationParameterPtr>*  inputParameters, CWnd* pParent = NULL);   // ��׼���캯��

	virtual ~OperationParameterDialog();

// �Ի�������
	enum { IDD = IDD_OPERATION_PARAMETER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	void SetPromptTitle();

	BOOL CreateParameterGrid();

	BOOL FillParameterGrid();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual BOOL OnInitDialog();
};
