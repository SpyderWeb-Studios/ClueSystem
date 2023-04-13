// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/EClueLocation.h"
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
	void UpdateNumberOfCluesInLocation(FString location, int Number)
	{
		NumberOfCluesInLocations.Add(location, Number);
		OnUpdateClueSectionSize.Broadcast(location, Number);
	};

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void SetClueConfigRoot(const FClueLocationConfig& Root);
	
	UFUNCTION()
	void BroadcastNumberOfClues();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasCollectedClue(UPrimaryDataAsset_Clue* ClueToCheck);
	
	UPROPERTY(BlueprintAssignable)
	FOnCollectedClue OnCollectedClue;
	
	UPROPERTY(BlueprintAssignable)
	FOnClueSelected OnClueSelected;
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdateClueLocation OnUpdateLocationClues;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateClueSectionSize OnUpdateClueSectionSize;

	UPROPERTY(BlueprintAssignable)
	FOnClueImageLoaded OnClueImageLoaded;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FString, int> NumberOfCluesInLocations;
	
protected:

	UPROPERTY(BlueprintReadOnly)
	FClueLocationConfig ClueConfigRoot;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FString, FAreaClues> CollectedClues;
	
	// Tree Structure
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<int, FClueTreeNode> ClueConfigTree;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void CreateTreeRecursively(UPrimaryDataAsset_ClueConfig* Config, TMap<int, FClueTreeNode>& Tree);
};
