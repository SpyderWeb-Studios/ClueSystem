// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TamperInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTamperInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TAMPERSYSTEM_API ITamperInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Tamper")
	bool CanBeTamperedWith();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Tamper")
	bool CanBeTamperedWithBy(UObject* Object);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Tamper")
	bool IsTamperValid(UObject* Object);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Tamper")
	bool AttemptApplyTamper(UObject* Object);
	
};
