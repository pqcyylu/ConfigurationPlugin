#include "StdAfx.h"
#include <boost/foreach.hpp>
#include "ConfigObjectViewModel.h"
#include "OperationTreeLoader.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include <vector>
using std::vector;

int OperationTreeLoader::OPERATION_ROOT_IMG_INDEX = 18;

int OperationTreeLoader::OPERATION_SET_IMG_INDEX = 21;

int OperationTreeLoader::OPERATION_QUERY_IMG_INDEX = 22;

OperationTreeLoader::OperationTreeLoader(void)
{
}

OperationTreeLoader::~OperationTreeLoader(void)
{
}

void OperationTreeLoader::LoadOpeartions(ConfigObjectViewModel& selectedCfgObjViewModel, CTreeCtrl& targetTreeCtrl)
{
	HTREEITEM rootItem = targetTreeCtrl.InsertItem(selectedCfgObjViewModel.GetName(), OPERATION_ROOT_IMG_INDEX, OPERATION_ROOT_IMG_INDEX);

	CObjInfo* configObject = selectedCfgObjViewModel.GetDataModel();
	if(NULL == configObject)
		return;

	vector<IMibCommand*> commands;
	configObject->GetQueryOperations(commands);

	BOOST_FOREACH(IMibCommand* curCommand, commands)
	{
		HTREEITEM curCmdItem = targetTreeCtrl.InsertItem(curCommand->GetDisplayName(), OPERATION_QUERY_IMG_INDEX, OPERATION_QUERY_IMG_INDEX, rootItem);
		if(curCmdItem == NULL)
			continue;

		targetTreeCtrl.SetItemData(curCmdItem, (DWORD_PTR)curCommand);
	}

	commands.clear();
	configObject->GetSetOperations(commands);
	BOOST_FOREACH(IMibCommand* curCommand, commands)
	{
		HTREEITEM curCmdItem = targetTreeCtrl.InsertItem(curCommand->GetDisplayName(), OPERATION_SET_IMG_INDEX, OPERATION_SET_IMG_INDEX, rootItem);
		if(curCmdItem == NULL)
			continue;

		targetTreeCtrl.SetItemData(curCmdItem, (DWORD_PTR)curCommand);
	}

	targetTreeCtrl.Expand(rootItem, TVE_EXPAND);
}
