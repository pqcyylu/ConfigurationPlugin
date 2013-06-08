#pragma once

class OperationTreeLoader
{
protected:
	OperationTreeLoader(void);

public:
	~OperationTreeLoader(void);

public:
	/*操作树根节点的Image索引*/
	static int OPERATION_ROOT_IMG_INDEX;

	/*查询操作的Image索引*/
	static int OPERATION_QUERY_IMG_INDEX;

	/*设置操作的Image索引*/
	static int OPERATION_SET_IMG_INDEX;

public:
	static void LoadOpeartions(ConfigObjectViewModel& selectedConfigObjectVM, CTreeCtrl& targetTreeCtrl);
};

