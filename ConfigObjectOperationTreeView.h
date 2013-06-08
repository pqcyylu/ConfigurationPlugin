#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// ConfigObjectOperationTreeView 窗体视图

class ConfigObjectOperationTreeView : public CFormView
{
	DECLARE_DYNCREATE(ConfigObjectOperationTreeView)

private:
	CStatic operationGroupCtrl;

	CTreeCtrl operationTreeCtrl;

	CImageList operationImages;

public:
	virtual void OnInitialUpdate();

	void UpdateView(class ConfigObjectViewModel* selectedCfgObjViewModel);

protected:
	ConfigObjectOperationTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~ConfigObjectOperationTreeView();

	void LoadImageList();

	void AdjustLayout();

public:
	enum { IDD = IDD_CONFIGOBJECTOPERATIONTREEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnOperationTreeDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
};


