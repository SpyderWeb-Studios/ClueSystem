// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable)
	static void DebugLog(FString message, EDebuggingType DebugType, float DisplayTime = 0.0f, FColor DisplayColour = FColor::Green);

	UFUNCTION(BlueprintCallable)
	static void DebugLogWithObject(UObject* Object,FString message, EDebuggingType DebugType, float DisplayTime = 0.0f, FColor DisplayColour = FColor::Green);
};
