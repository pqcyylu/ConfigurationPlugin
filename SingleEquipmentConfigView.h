#pragma once

#include "ConfigObjectGridCtrl.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "afxwin.h"

// SingleEquipmentConfigView form view
class SingleEquipmentConfigView : public CFormView
{
	DECLARE_DYNCREATE(SingleEquipmentConfigView)

private:
	ConfigObjectGridCtrl configObjectGridCtrl;

protected:
	SingleEquipmentConfigView();           // protected constructor used by dynamic creation
	virtual ~SingleEquipmentConfigView();

public:
	enum { IDD = IDD_SINGLEEQUIPMENTCONFIGVIEW };

	void UpdateView(IMibInstanceTablePtr instanceTablePtr);

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void AdjustLayout();

	IMibInstance* GetInstanceFromSelectedItem(CBCGPGridItem* selectedItem);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg LRESULT OnUpdateView(WPARAM wpInstanceTable, LPARAM lpParam);

	afx_msg LRESULT OnConfigGridContrlDoubleClick(WPARAM wParam, LPARAM lParam);
	CStatic instanceGroup;
};


