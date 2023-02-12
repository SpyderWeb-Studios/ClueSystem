// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/EClueLocation.h"
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

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	bool CollectClue(UPrimaryDataAsset_Clue* Clue);

	UFUNCTION(BlueprintCallable)
	void UpdateNumberOfCluesInLocation(EClueLocation location, int Number)
	{
		NumberOfCluesInLocations.Add(location, Number);
		OnUpdateClueSectionSize.Broadcast(location, Number);
	};

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
	TMap<TEnumAsByte<EClueLocation>, int> NumberOfCluesInLocations;
	
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TEnumAsByte<EClueLocation>, FAreaClues> CollectedClues;
	
	
	
};
