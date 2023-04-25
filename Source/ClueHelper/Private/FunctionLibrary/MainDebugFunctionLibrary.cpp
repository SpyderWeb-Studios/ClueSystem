// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "FunctionLibrary/MainDebugFunctionLibrary.h"

#include "Engine/Engine.h"


void UMainDebugFunctionLibrary::DebugLog(FString message, EDebuggingType DebugType, float DisplayTime, FColor DisplayColour)
{
	switch (DebugType) {

	case EDebuggingType::DT_Screen:
		GEngine->AddOnScreenDebugMessage(0, DisplayTime, DisplayColour, message);
		break;
	case EDebuggingType::DT_Log:
		UE_LOG(LogBlueprint, Warning, TEXT("%s"), *message);
		break;
	case EDebuggingType::DT_Both:
		GEngine->AddOnScreenDebugMessage(0, DisplayTime, DisplayColour, message);
		UE_LOG(LogBlueprint, Warning, TEXT("%s"), *message);
		break;
	}
}

void UMainDebugFunctionLibrary::DebugLogWithObject(UObject* Object, FString message, EDebuggingType DebugType = EDebuggingType::DT_Log, float DisplayTime, FColor DisplayColour)
{
	if (Object) message = Object->GetFName().ToString()+ ": " + message;
	DebugLog(message, DebugType, DisplayTime, DisplayColour);
}
