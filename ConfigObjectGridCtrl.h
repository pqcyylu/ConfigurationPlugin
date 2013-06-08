//===========================================================================//
//  FILE:  ConfigObjectGridCtrl.h											//
//------------------------------------------------------------------------	//
//	PURPOSE:																//
//	   	网元配置对象的实例呈现Grid。												//
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
	/*清除所有列*/
	void ClearView();

	/*创建显示列*/
	void CreateColumns(IMibInstanceTablePtr instanceTable);

	/*填充所有行*/
	void FillRows(IMibInstanceTablePtr instanceTable);

	/*填充一行*/
	void FillRow(IMibInstance* fillInstance);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


