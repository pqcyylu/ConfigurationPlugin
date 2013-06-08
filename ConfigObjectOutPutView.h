#pragma once
#include "afxwin.h"

// ConfigObjectOutPutView ������ͼ

class ConfigObjectOutPutView : public CFormView
{
	DECLARE_DYNCREATE(ConfigObjectOutPutView)

private:
	CStatic outputGroupCtrl;

protected:
	ConfigObjectOutPutView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~ConfigObjectOutPutView();

	void AdjustLayout();

public:
	enum { IDD = IDD_CONFIGOBJECTOUTPUTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()	

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


