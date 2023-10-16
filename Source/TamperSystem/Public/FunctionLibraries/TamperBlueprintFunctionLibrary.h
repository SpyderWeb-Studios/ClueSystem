// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TamperComponent.h"
#include "GameFramework/TamperObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TamperBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TAMPERSYSTEM_API UTamperBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Tamper", BlueprintInternalUseOnly = "true"), Category = "Tamper System|Function Library")
	static UTamperObject* AddTamper(TSubclassOf<UTamperObject> TamperClass, UObject* TargetObject, bool bAutoActivate = true);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Register Tamper", BlueprintInternalUseOnly = "true"), Category =  "Tamper System|Function Library")
	static UTamperObject* RegisterTamperObject(UObject* Target, UTamperObject* TamperObject);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, meta = (DisplayName = "Destroy TamperObject"), Category =  "Tamper System|Function Library")
	static void DestroyTamperObject(UTamperObject* TamperObject);
	
};
