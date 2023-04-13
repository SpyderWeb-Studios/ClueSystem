// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryDataAsset_Clue.h"
#include "Engine/DataAsset.h"
#include "PrimaryDataAsset_ClueConfig.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UPrimaryDataAsset_ClueConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "ClueSystem")
	FString GetClueLocation() const { return ClueLocation; }

	UFUNCTION(BlueprintPure, Category="ClueSystem")
	TArray<UPrimaryDataAsset_Clue*> GetClues() const { return Clues; }

	UFUNCTION(BlueprintPure, Category="ClueSystem")
	TArray<UPrimaryDataAsset_ClueConfig*> GetBranches() const { return Branches; }
	
	void UpdateClueIndices(FString Location);

	UFUNCTION(BlueprintPure)
	int GetIndex() const { return Index; }

	UFUNCTION(BlueprintCallable)
	void SetIndex(int NewIndex) { Index = NewIndex; }
	
	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	FString ClueLocation; 

	UPROPERTY(VisibleAnywhere, Transient)
	int Index;

	UPROPERTY(EditDefaultsOnly)
	TArray<UPrimaryDataAsset_ClueConfig*> Branches;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UPrimaryDataAsset_Clue*> Clues;
	
	bool operator==(const UPrimaryDataAsset_ClueConfig& Other) const
	{
		return ClueLocation == Other.ClueLocation;
	}
	
};
