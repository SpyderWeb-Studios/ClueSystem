// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryDataAsset_Clue.h"
#include "Engine/DataAsset.h"
#include "Libraries/EventDelegateLibrary.h"
#include "Widgets/Manager/ClueBranchManager.h"
#include "PrimaryDataAsset_ClueConfig.generated.h"

/**
 * This Data Asset Class is an abstract way to determine the structure of the Clue Tree. It holds the vital
 * information like how each branch is structured, what clues are in each branch, and what the name of the location is.
 */
UCLASS()
class CLUESYSTEM_API UPrimaryDataAsset_ClueConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "ClueSystem|ClueBranchManager")
	FString GetClueLocation() const { return ClueLocation; }

	UFUNCTION(BlueprintPure, Category="ClueSystem|ClueBranchManager")
	TArray<UPrimaryDataAsset_Clue*> GetClues() const { return Clues; }

	UFUNCTION(BlueprintPure, Category="ClueSystem|ClueBranchManager")
	TArray<UPrimaryDataAsset_ClueConfig*> GetBranches() const { return Branches; }
	
	void UpdateClueIndices(FString Location);

	UFUNCTION(BlueprintPure, Category="ClueSystem|ClueBranchManager")
	int GetIndex() const { return Index; }

	UFUNCTION(BlueprintCallable, Category="ClueSystem|ClueBranchManager")
	void SetIndex(int NewIndex) { Index = NewIndex; }

	FClueTree GetClueTree() const;

	UFUNCTION(BlueprintPure, Category="ClueSystem|ClueBranchManager")
	TSubclassOf<UClueBranchManager> GetClueBranchManagerClass() const { return ClueBranchManagerClass; }

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="ClueSystem")
	FString ClueLocation; 

	UPROPERTY(EditDefaultsOnly, Category="ClueSystem")
	TSubclassOf<UClueBranchManager> ClueBranchManagerClass;
	
	UPROPERTY(VisibleAnywhere, Transient, Category="ClueSystem")
	int Index;

	UPROPERTY(EditDefaultsOnly, Category="ClueSystem")
	TArray<UPrimaryDataAsset_ClueConfig*> Branches;
	
	UPROPERTY(EditDefaultsOnly, Category="ClueSystem")
	TArray<UPrimaryDataAsset_Clue*> Clues;
	
	bool operator==(const UPrimaryDataAsset_ClueConfig& Other) const
	{
		return ClueLocation == Other.ClueLocation;
	}
	
};
