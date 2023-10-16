// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TamperObject.generated.h"

/**
 * Each Subclass of this class will be define a new way to tamper with another object that implement the ITamperable interface
 */
UCLASS(Blueprintable, BlueprintType)
class TAMPERSYSTEM_API UTamperObject : public UObject
{
	GENERATED_BODY()

public:

	
};
