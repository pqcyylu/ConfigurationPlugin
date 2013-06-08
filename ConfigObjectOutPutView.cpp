// ConfigObjectOutPutView.cpp : 实现文件
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


// ConfigObjectOutPutView 诊断

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

	/*计算提示文本串“管理对象：”的文本高度，用于排列各控件*/
	int groupTextHeight = 0;
	if(outputGroupCtrl.GetSafeHwnd() != NULL)
	{
		groupTextHeight = ControlLayoutHelper::CalculateHeaderTextHeight(outputGroupCtrl);

		outputGroupCtrl.SetWindowPos(NULL, 0, 0, rectClient.Width()+1, rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


// ConfigObjectOutPutView 消息处理程序


void ConfigObjectOutPutView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AdjustLayout();
}


int ConfigObjectOutPutView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	AdjustLayout();

	return 0;
}
