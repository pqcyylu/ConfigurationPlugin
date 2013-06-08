#pragma once

#include "DTUtilityInc/DTSingleton.h"
#include "NetElementModelInc/NetElementModelExport.h"
#include "ConfigDocumentBase.h"
#include "OperationParameter.h"

class ConfigObjectOperationHandler
{
	DECLARE_SINGLETON_NOINIT(ConfigObjectOperationHandler)

public:
	int HandleOperation(IMibCommand& command, ConfigDocumentBase& hostDocument);

protected:
	BOOL CreateUserInputParameters(IMibCommand& command, ConfigObjectViewModel& cfgObjectViewModel, vector<OperationParameterPtr>& userInputs);

	BOOL CreateIndexParameters(ConfigObjectViewModel& cfgObjectViewModel, vector<OperationParameterPtr>& userInputs);
};

