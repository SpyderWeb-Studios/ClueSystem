// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "UObject/Interface.h"
#include "ClueObjectInterface.generated.h"

class UPrimaryDataAsset_Clue;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClueObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLUESYSTEM_API IClueObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, BlueprintCallable, Category="ClueObjectInterface")
	UPrimaryDataAsset_Clue* GetClueDataAsset();

		
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, BlueprintCallable)
	bool SetClueDataAsset(UPrimaryDataAsset_Clue* ClueDataAsset);
};
