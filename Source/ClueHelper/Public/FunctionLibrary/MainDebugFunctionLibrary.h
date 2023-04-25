// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enums/EDebuggingType.h"
#include "MainDebugFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CLUEHELPER_API UMainDebugFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category="Main Debug Library")
	static void DebugLog(FString message, EDebuggingType DebugType, float DisplayTime = 0.0f, FColor DisplayColour = FColor::Green);

	UFUNCTION(BlueprintCallable, Category="Main Debug Library")
	static void DebugLogWithObject(UObject* Object,FString message, EDebuggingType DebugType, float DisplayTime = 0.0f, FColor DisplayColour = FColor::Green);
};
