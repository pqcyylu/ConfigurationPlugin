// WaitDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "WaitDialog.h"
#include "afxdialogex.h"
#include "DTUtilityInc/DTUtilityInc.h"

extern AFX_EXTENSION_MODULE ConfigurationPluginDLL;

// WaitDialog dialog

IMPLEMENT_DYNAMIC(WaitDialog, CDialogEx)

WaitDialog::WaitDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(WaitDialog::IDD, pParent)
{

}

WaitDialog::~WaitDialog()
{
}

void WaitDialog::DoDataExchange(CDataExchange* pDX)
{	
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAIT_DISPLAY_CTRL, waitAnimationPicture);
}


BEGIN_MESSAGE_MAP(WaitDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &WaitDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// WaitDialog message handlers


BOOL WaitDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString animationPicPath = CDTPathUtility::GetInstance()->GetAppResourcePath().c_str();
	animationPicPath += "\\BMP\\waiting.gif";

	if(waitAnimationPicture.Load(animationPicPath))
		waitAnimationPicture.Draw();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void WaitDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
