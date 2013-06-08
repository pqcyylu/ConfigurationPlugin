#pragma once

#include "ConfigDocumentBase.h"
#include "NetElementModelInc/NetElementModelExport.h"

// SingleEquipmentConfigDoc document
class NetElementViewModel;

class SingleEquipmentConfigDoc : public ConfigDocumentBase
{
	DECLARE_DYNCREATE(SingleEquipmentConfigDoc)

private:
	/*Document����Ӧ����ԪViewModel*/
	NetElementViewModel* hostNetElementViewModel;

	/*��ȡ����ʵ�����߳̾�������ں����û���ͣ��ѯ*/
	AsyncGetInstancePtr getInstancePtr;

	/*��ǰ�û�ѡ�еĵĶ���ʵ����*/
	IMibInstanceTablePtr instanceTablePtr;

	CWnd* waitWindow;

public:
	SingleEquipmentConfigDoc();
	virtual ~SingleEquipmentConfigDoc();

public:
	virtual void SetSelectedConfigObjectViewModel(ConfigObjectViewModel* selectedCfgObjViewModel);

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

	void GetInstanceCallBack(IMibInstanceTablePtr mibIntanceTable);

	void SetInstanceTable(IMibInstanceTablePtr mibInstanceTable);

	void UpdateInstancesViews(IMibInstanceTablePtr mibInstanceTable);

	void UpdateOperationView(ConfigObjectViewModel* selectedCfgObjViewModel);

	void CloseWaitWindows();

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
