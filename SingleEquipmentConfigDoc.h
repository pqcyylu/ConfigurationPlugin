#pragma once

#include "ConfigDocumentBase.h"
#include "NetElementModelInc/NetElementModelExport.h"

// SingleEquipmentConfigDoc document
class NetElementViewModel;

class SingleEquipmentConfigDoc : public ConfigDocumentBase
{
	DECLARE_DYNCREATE(SingleEquipmentConfigDoc)

private:
	/*Document所对应的网元ViewModel*/
	NetElementViewModel* hostNetElementViewModel;

	/*获取对象实例的线程句柄，由于后续用户暂停查询*/
	AsyncGetInstancePtr getInstancePtr;

	/*当前用户选中的的对象实例表*/
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
