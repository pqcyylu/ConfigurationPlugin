//===========================================================================//
//  FILE:  ConfigObjectGridCtrl.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	��Ԫ���ö����ʵ������Grid��												//
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
//	 2013-05-16 - create by pengqiang										//
//==========================================================================//
#pragma once

#include <BCGCBPro/BCGCBProInc.h>
#include "NetElementModelInc/NetElementModelExport.h"

// ConfigObjectGridCtrl

class ConfigObjectGridCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(ConfigObjectGridCtrl)

public:
	ConfigObjectGridCtrl();
	virtual ~ConfigObjectGridCtrl();

public:
	void UpdateView(IMibInstanceTablePtr instanceTable);

protected:
	/*���������*/
	void ClearView();

	/*������ʾ��*/
	void CreateColumns(IMibInstanceTablePtr instanceTable);

	/*���������*/
	void FillRows(IMibInstanceTablePtr instanceTable);

	/*���һ��*/
	void FillRow(IMibInstance* fillInstance);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


