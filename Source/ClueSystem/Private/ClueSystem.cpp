// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#include "ClueSystem.h"

#define LOCTEXT_NAMESPACE "FClueSystemModule"
DEFINE_LOG_CATEGORY(LogClue);
void FClueSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FClueSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FClueSystemModule, ClueSystem)