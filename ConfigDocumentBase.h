#pragma once

#include <vector>
using std::vector;

class ConfigObjectViewModel;

// ConfigDocumentBase document

class ConfigDocumentBase : public CDocument
{
	DECLARE_DYNCREATE(ConfigDocumentBase)

protected:
	/*配置信息的版本号*/
	CString configInfoVersionNo;

	vector<ConfigObjectViewModel*> configObjectViewModels;

	/*当前选中的配置对象模型*/
	ConfigObjectViewModel* selectedConfigObjectViewModel;

public:
	ConfigDocumentBase();
	virtual ~ConfigDocumentBase();

public:
	CString GetConfigInfoVersionNo();

	void AddConfigObjectViewModel(ConfigObjectViewModel* addViewModel);

	/*设置要显示的ConfigObject*/
	virtual void SetSelectedConfigObjectViewModel(ConfigObjectViewModel* selectedCfgObjViewModel);

	ConfigObjectViewModel* GetSelectedConfigObjectViewModel();

protected:
	void SetConfigInfoVersionNo(const CString& versionNo);

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
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()

};
