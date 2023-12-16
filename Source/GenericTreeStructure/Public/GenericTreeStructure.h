﻿#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGenericTreeStructureModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogGenericTree, Log, All);