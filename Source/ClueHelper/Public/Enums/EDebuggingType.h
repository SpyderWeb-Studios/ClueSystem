// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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