// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "EDebuggingType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDebuggingType : uint8 {
	DT_Screen,
	DT_Log,
	DT_Both
};