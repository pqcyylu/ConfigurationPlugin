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

	/*������Ҫ�û�����Ĳ���*/
	vector<OperationParameterPtr> userInputParameters;
	if(!CreateUserInputParameters(command, *cfgObjVM, userInputParameters))
	{
		return -1;
	}

	/*��ȡ�û�����*/
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
		/*��ѯ����ֻ��Ҫ�û���������*/
		return TRUE;
	}

	int parameteCount = command.ParameterCount();
	for(int curParameterIndex=0; curParameterIndex<parameteCount; curParameterIndex++)
	{
		IMibNode* curMibNode = command.GetParameter(curParameterIndex);
		if(curMibNode == NULL)
		{
			L_ERROR("����MIB�ڵ�Ϊ�գ��޷����к����������!");
			return FALSE;
		}

		/*��״̬�ڵ㲻��Ϊ�û�������ʾ*/
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

	/*������������*/
	int indexNum = configObject->GetIndexNum();
	for(int curIndex=0; curIndex < indexNum; curIndex++)
	{
		IMibNode* curIndexMibNode = configObject->GetIndex(curIndex);

		if(NULL == curIndexMibNode)
		{
			L_ERROR("�����ڵ�Ϊ�գ��޷����к����������!");
			return FALSE;
		}

		userInputs.push_back(OperationParameterFactory::GetInstance()->CreateOperationParameter(curIndexMibNode, ""));
	}

	return TRUE;
}
