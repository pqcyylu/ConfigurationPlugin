// ConfigObjectOutPutView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "ConfigObjectOutPutView.h"
#include "ControlLayoutHelper.h"


// ConfigObjectOutPutView

IMPLEMENT_DYNCREATE(ConfigObjectOutPutView, CFormView)

ConfigObjectOutPutView::ConfigObjectOutPutView()
	: CFormView(ConfigObjectOutPutView::IDD)
{

}

ConfigObjectOutPutView::~ConfigObjectOutPutView()
{
}

void ConfigObjectOutPutView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_OUTPUT_GROUP, outputGroupCtrl);
}

BEGIN_MESSAGE_MAP(ConfigObjectOutPutView, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// ConfigObjectOutPutView ���

#ifdef _DEBUG
void ConfigObjectOutPutView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ConfigObjectOutPutView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void ConfigObjectOutPutView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	ShowScrollBar(SB_BOTH,FALSE);

	CRect rectClient;
	GetClientRect(rectClient);

	/*������ʾ�ı�����������󣺡����ı��߶ȣ��������и��ؼ�*/
	int groupTextHeight = 0;
	if(outputGroupCtrl.GetSafeHwnd() != NULL)
	{
		groupTextHeight = ControlLayoutHelper::CalculateHeaderTextHeight(outputGroupCtrl);

		outputGroupCtrl.SetWindowPos(NULL, 0, 0, rectClient.Width()+1, rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


// ConfigObjectOutPutView ��Ϣ�������


void ConfigObjectOutPutView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AdjustLayout();
}


int ConfigObjectOutPutView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	AdjustLayout();

	return 0;
}
