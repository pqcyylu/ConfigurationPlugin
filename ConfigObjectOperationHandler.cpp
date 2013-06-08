#include "StdAfx.h"
#include "boost/make_shared.hpp"
#include "resource.h"
#include "ConfigObjectViewModel.h"
#include "ConfigObjectOperationHandler.h"
#include "OperationParameter.h"
#include "OperationParameterDialog.h"
#include "OperationParameterFactory.h"
#include "AveLogMacro.h"

IMPLEMENT_SINGLETON(ConfigObjectOperationHandler)

int ConfigObjectOperationHandler::HandleOperation(IMibCommand& command, ConfigDocumentBase& hostDocument)
{
	ConfigObjectViewModel* cfgObjVM = hostDocument.GetSelectedConfigObjectViewModel();
	if(cfgObjVM == NULL)
		return -1;

	/*构造需要用户输入的参数*/
	vector<OperationParameterPtr> userInputParameters;
	if(!CreateUserInputParameters(command, *cfgObjVM, userInputParameters))
	{
		return -1;
	}

	/*获取用户输入*/
	OperationParameterDialog userInputParametersDlg(command, &userInputParameters);
	userInputParametersDlg.DoModal();

	return -1;
}

BOOL ConfigObjectOperationHandler::CreateUserInputParameters(IMibCommand& command, ConfigObjectViewModel& cfgObjectViewModel, vector<OperationParameterPtr>& userInputs)
{
	if( !CreateIndexParameters(cfgObjectViewModel, userInputs) )
	{
		return FALSE;
	}

	if(command.GetType() == COMMANDTYPE_QUERY )
	{
		/*查询命令只需要用户输入索引*/
		return TRUE;
	}

	int parameteCount = command.ParameterCount();
	for(int curParameterIndex=0; curParameterIndex<parameteCount; curParameterIndex++)
	{
		IMibNode* curMibNode = command.GetParameter(curParameterIndex);
		if(curMibNode == NULL)
		{
			L_ERROR("参数MIB节点为空，无法进行后续的命令处理!");
			return FALSE;
		}

		/*行状态节点不作为用户输入显示*/
		if(RowStatusNode == curMibNode->GetNodeType())
			continue;

		userInputs.push_back(OperationParameterFactory::GetInstance()->CreateOperationParameter(curMibNode, ""));
	}

	return TRUE;
}

BOOL ConfigObjectOperationHandler::CreateIndexParameters(ConfigObjectViewModel& cfgObjectViewModel, vector<OperationParameterPtr>& userInputs)
{
	CObjInfo* configObject = cfgObjectViewModel.GetDataModel();
	if(NULL == configObject)
		return FALSE;

	/*构造索引参数*/
	int indexNum = configObject->GetIndexNum();
	for(int curIndex=0; curIndex < indexNum; curIndex++)
	{
		IMibNode* curIndexMibNode = configObject->GetIndex(curIndex);

		if(NULL == curIndexMibNode)
		{
			L_ERROR("索引节点为空，无法进行后续的命令处理!");
			return FALSE;
		}

		userInputs.push_back(OperationParameterFactory::GetInstance()->CreateOperationParameter(curIndexMibNode, ""));
	}

	return TRUE;
}
