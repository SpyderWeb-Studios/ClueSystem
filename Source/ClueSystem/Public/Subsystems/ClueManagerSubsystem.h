// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/ClueStructLibrary.h"
#include "Libraries/EventDelegateLibrary.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "ClueManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UClueManagerSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	bool CollectClue(UPrimaryDataAsset_Clue* Clue);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Clue System|Clue Manager|Setup")
	void CreateTreeRecursively(UPrimaryDataAsset_ClueConfig* Config, TMap<int, FClueTreeNode>& Tree);
	
	UFUNCTION(BlueprintCallable, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, We are using the Tree System Now"), Category="Clue System|Clue Manager|Setup")
	void UpdateNumberOfCluesInLocation(FString ParentBranch, FString location, int Number);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Clue System|Clue Manager|Setup")
	void SetClueConfigRoot(UPrimaryDataAsset_ClueConfig* Root);


#pragma region Events
	
	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnCollectedClue OnCollectedClue;
	
	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnClueSelected OnClueSelected;

	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnClueImageLoaded OnClueImageLoaded;

	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnUpdateClueTree OnClueTrueCreated;

#pragma endregion

#pragma region Utility
		
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Clue System|Clue Manager|Utility")
	bool HasCollectedClue(UPrimaryDataAsset_Clue* ClueToCheck);
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System|Clue Manager|Utility")
	TMap<FString, int> NumberOfCluesInLocations;

	UFUNCTION(BlueprintPure, Category="Clue System|Clue Manager|Utility")
	int GetNumberOfCluesInLocation(FString Location) const;

	UFUNCTION(BlueprintPure, Category="Clue System|Clue Manager|Utility")
	int GetNumberOfCollectedCluesInLocation(FString Location) const;

	UFUNCTION(BlueprintPure, Category="Clue System|Clue Manager|Utility")
	int GetIndexFromName(FString ClueName) const;
	
	UFUNCTION(BlueprintPure, Category="Clue System|Clue Manager|Utility")
	int GetParentIndexFromIndex(int Index) const;

	UFUNCTION(BlueprintPure, Category="Clue System|Clue Manager|Utility")
	int GetParentIndexFromName(FString ClueName) const;

	UFUNCTION(BlueprintPure, Category="Clue System|Clue Manager|Utility")
	TMap<int, FClueTreeNode> GetClueTree() const;
	
	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Manager|Utility")
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromIndex(int Index) const;

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Manager|Utility")
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromName(FString ClueName) const;

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Manager|Utility")
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromParentIndex(int ParentIndex, FString ClueLocation) const;

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Manager|Utility")
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromParentName(FString ParentName, FString ClueLocation) const;

#pragma endregion 

protected:

	UPROPERTY(BlueprintReadOnly, Category="Clue System|Clue Manager")
	TObjectPtr<UPrimaryDataAsset_ClueConfig> ClueConfigRoot;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System|Clue Manager")
	TMap<FString, FAreaClues> CollectedClues;
	
	// Tree Structure
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System|Clue Manager")
	TMap<int, FClueTreeNode> ClueConfigTree;

};
