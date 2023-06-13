// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ClueManagerComponent.h"
#include "UObject/Interface.h"
#include "PlayerClueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerClueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLUESYSTEM_API IPlayerClueInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, BlueprintCallable, Category="Clue System|Clue")
	UClueManagerComponent* GetClueManager() const;
};
