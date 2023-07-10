// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClueBranchBrush.generated.h"

struct FStreamableHandle;
class UPrimaryDataAsset_ClueConfig;
/**
 * The purpose of the ClueBranchBrush is to listen for when the Nodes that it has registered have collapsed. Once all
 * of the Clues have been selected within the Location defined by this Volume, it adds the updated ClueConfig to the Clue Manager Component.
 * Once all of the Volumes have been added to the Clue Manager Component, it generates the Clue Tree. 
 */
UCLASS()
class CLUESYSTEM_API AClueBranchBrush : public AVolume
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Clue Branch Setup")
	TObjectPtr<UPrimaryDataAsset_ClueConfig> ConnectedConfig;

	
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, CallInEditor, Category="Clue Branch Setup")
	bool RegisterCluesInRange();

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Clue Branch Setup")
	void TestRegister();
	
};
