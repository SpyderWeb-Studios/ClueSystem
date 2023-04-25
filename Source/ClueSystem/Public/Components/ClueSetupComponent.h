// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
#include "ClueSetupComponent.generated.h"


UCLASS( ClassGroup=("Clue System"), meta=(BlueprintSpawnableComponent) )
class CLUESYSTEM_API UClueSetupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClueSetupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// This will be a Root Node generated using a ClueConfig Data Asset
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System Configuration")
	TObjectPtr<UPrimaryDataAsset_ClueConfig> ClueConfig;

		
};
