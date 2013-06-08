#pragma once

class ConfigDocumentNameUtil
{
protected:
	ConfigDocumentNameUtil(void);

public:
	~ConfigDocumentNameUtil(void);

public:
	static CString CreateSingleEquipmentConfigDocumentName();

	static CString CreateBatchConfigDocumentName();
};

