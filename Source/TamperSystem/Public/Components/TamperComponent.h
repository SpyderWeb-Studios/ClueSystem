// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/TamperInterface.h"
#include "TamperComponent.generated.h"


class UTamperObject;
UCLASS( ClassGroup=("Tamper System"), meta=(BlueprintSpawnableComponent) )
class TAMPERSYSTEM_API UTamperComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTamperComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, BlueprintCallable, Category = "Tamper System|Component")
	bool AttemptTamper(TSubclassOf<UTamperObject> TamperClass, UObject* TamperTarget);
			
};
