#pragma once

#include "UIControlLibInc/UIControlLibExport.h"
#include "afxwin.h"


// WaitDialog dialog

class WaitDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WaitDialog)

public:
	CPictureEx waitAnimationPicture;

public:
	WaitDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~WaitDialog();

// Dialog Data
	enum { IDD = IDD_WAIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
};
