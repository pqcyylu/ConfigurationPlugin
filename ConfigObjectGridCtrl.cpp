//===========================================================================//
//  FILE:  ConfigObjectGridCtrl.cpp											//
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

#include "stdafx.h"
#include "ConfigObjectGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static BCGP_GRID_COLOR_DATA GridCtrlTheme = 
{
	-1,	// Grid background color
	-1,	// Grid foreground color
	-1,	// Header foreground color

	{	// Even rows colors:
		RGB (246, 250, 253), -1, -1, 0, -1
	},

	{	// Odd rows colors:
		-1, -1, -1, 0, -1
		},

		{	// Group colors:
			RGB (210, 230, 249), RGB (16, 37, 127), RGB (228, 241, 251), 90, -1
		},

		{	// Selected group colors:
			RGB (250, 199, 97), RGB (0, 0, 0), -1, 0, RGB (192, 192, 192)
			},

			{	// Selected rows colors:
				RGB (255, 229, 153), -1, -1, 0, RGB (192, 192, 192)
			},

			{	// Header item colors:
				RGB (154, 194, 237), RGB (16, 37, 127), RGB (189, 214, 242), 90, RGB (136, 176, 228)
				},

				{	// Selected header item colors:
					-1, -1, -1, 0, -1
				},

				{	// Left offset colors:
					RGB (207, 221, 240), -1, RGB (227, 234, 244), 90, RGB (136, 176, 228)
					},

					-1,	// Grid horizontal line text
					-1,	// Grid vertical line text
					-1,	// Description text color
};

// ConfigObjectGridCtrl
IMPLEMENT_DYNAMIC(ConfigObjectGridCtrl, CBCGPGridCtrl)

ConfigObjectGridCtrl::ConfigObjectGridCtrl()
{

}

ConfigObjectGridCtrl::~ConfigObjectGridCtrl()
{
}


BEGIN_MESSAGE_MAP(ConfigObjectGridCtrl, CBCGPGridCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// ConfigObjectGridCtrl message handlers
int ConfigObjectGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableMarkSortedColumn (TRUE, FALSE);
	EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_SORT);
	EnableRowHeader(TRUE);
	EnableLineNumbers();
	EnableInvertSelOnCtrl();

	//-------------
	// Add columns:
	//-------------
	SetColorTheme(GridCtrlTheme);

	SetReadOnly();

	SetWholeRowSel(TRUE);

	EnableGroupByBox(TRUE);

	AdjustLayout();

	return 0;
}

void ConfigObjectGridCtrl::UpdateView(IMibInstanceTablePtr instanceTable)
{
	ClearView();

	CreateColumns(instanceTable);

	FillRows(instanceTable);

	AdjustLayout();
}

void ConfigObjectGridCtrl::ClearView()
{
	RemoveAll();

	DeleteAllColumns();
}

void ConfigObjectGridCtrl::CreateColumns(IMibInstanceTablePtr instanceTable)
{	
	int columnCount = instanceTable->GetFieldCount();

	for(int curColumnIndex=0; curColumnIndex < columnCount; curColumnIndex++)
	{
		IMibNode* curField = instanceTable->GetField(curColumnIndex);
		if(NULL == curField)
			continue;

		InsertColumn(curColumnIndex, curField->GetFriendName(), 80);

		SetHeaderAlign(curColumnIndex, HDF_CENTER);
		SetColumnAlign(curColumnIndex, HDF_CENTER);

		if(curField->IsIndex())
		{
			InsertGroupColumn(curColumnIndex, curColumnIndex);
			SetColumnVisible(curColumnIndex, FALSE);
		}
	}
}

void ConfigObjectGridCtrl::FillRows(IMibInstanceTablePtr instanceTable)
{
	int instanceCount = instanceTable->GetInstanceCount();

	for(int curIndex=0; curIndex < instanceCount; curIndex++)
	{
		IMibInstance* curInstance = instanceTable->GetInstance(curIndex);

		if(NULL == curInstance)
			continue;

		FillRow(curInstance);
	}
}

void ConfigObjectGridCtrl::FillRow(IMibInstance* fillInstance)
{
	CBCGPGridRow* pRow = CreateRow (GetColumnCount ());

	for (int columnIndex = 0; columnIndex < GetColumnCount (); columnIndex++)
	{
		IMibNodeValue* curNodeValue = fillInstance->GetValue(columnIndex);
		if(NULL == curNodeValue)
			continue;

		pRow->GetItem(columnIndex)->SetValue((LPCSTR)curNodeValue->GetDisplayValue(), FALSE);
	}

	AddRow (pRow, FALSE);
	pRow->SetData((DWORD_PTR)fillInstance);
}

