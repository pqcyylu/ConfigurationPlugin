#pragma once

class OperationTreeLoader
{
protected:
	OperationTreeLoader(void);

public:
	~OperationTreeLoader(void);

public:
	/*���������ڵ��Image����*/
	static int OPERATION_ROOT_IMG_INDEX;

	/*��ѯ������Image����*/
	static int OPERATION_QUERY_IMG_INDEX;

	/*���ò�����Image����*/
	static int OPERATION_SET_IMG_INDEX;

public:
	static void LoadOpeartions(ConfigObjectViewModel& selectedConfigObjectVM, CTreeCtrl& targetTreeCtrl);
};

