#pragma once

#include <vector>
using std::vector;

class ConfigObjectViewModel;

// ConfigDocumentBase document

class ConfigDocumentBase : public CDocument
{
	DECLARE_DYNCREATE(ConfigDocumentBase)

protected:
	/*������Ϣ�İ汾��*/
	CString configInfoVersionNo;

	vector<ConfigObjectViewModel*> configObjectViewModels;

	/*��ǰѡ�е����ö���ģ��*/
	ConfigObjectViewModel* selectedConfigObjectViewModel;

public:
	ConfigDocumentBase();
	virtual ~ConfigDocumentBase();

public:
	CString GetConfigInfoVersionNo();

	void AddConfigObjectViewModel(ConfigObjectViewModel* addViewModel);

	/*����Ҫ��ʾ��ConfigObject*/
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
