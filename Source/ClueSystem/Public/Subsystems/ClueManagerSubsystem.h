// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Libraries/ClueConfig.h"
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


	UFUNCTION(BlueprintCallable, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, We are using the Tree System Now"))
	void UpdateNumberOfCluesInLocation(FString ParentBranch, FString location, int Number);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void SetClueConfigRoot(const FClueLocationConfig& Root);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasCollectedClue(UPrimaryDataAsset_Clue* ClueToCheck);
	
	UPROPERTY(BlueprintAssignable)
	FOnCollectedClue OnCollectedClue;
	
	UPROPERTY(BlueprintAssignable)
	FOnClueSelected OnClueSelected;

	UPROPERTY(BlueprintAssignable)
	FOnClueImageLoaded OnClueImageLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateClueTree OnClueTrueCreated;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FString, int> NumberOfCluesInLocations;

	UFUNCTION(BlueprintPure)
	int GetNumberOfCluesInLocation(FString Location) const;

	UFUNCTION(BlueprintPure)
	int GetNumberOfCollectedCluesInLocation(FString Location) const;

	UFUNCTION(BlueprintPure)
	int GetIndexFromName(FString ClueName) const;
	
	UFUNCTION(BlueprintPure)
	int GetParentIndexFromIndex(int Index) const;

	UFUNCTION(BlueprintPure)
	int GetParentIndexFromName(FString ClueName) const;

	UFUNCTION(BlueprintPure)
	TMap<int, FClueTreeNode> GetClueTree() const;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void CreateTreeRecursively(UPrimaryDataAsset_ClueConfig* Config, TMap<int, FClueTreeNode>& Tree);

	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromIndex(int Index) const;

	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromName(FString ClueName) const;

	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromParentIndex(int ParentIndex, FString ClueLocation) const;

	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfigFromParentName(FString ParentName, FString ClueLocation) const;


protected:

	UPROPERTY(BlueprintReadOnly)
	FClueLocationConfig ClueConfigRoot;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FString, FAreaClues> CollectedClues;
	
	// Tree Structure
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<int, FClueTreeNode> ClueConfigTree;

};
