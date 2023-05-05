// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

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
class CLUESYSTEM_API UClueManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UClueManagerSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void Cleanup();
	
		
	bool CollectClue(UPrimaryDataAsset_Clue* Clue);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Clue System|Clue Manager|Setup")
	void CreateTreeRecursively(UPrimaryDataAsset_ClueConfig* Config, TMap<int, FClueTreeNode>& Tree);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Clue System|Clue Manager|Setup")
	void SetClueConfigRoot(UPrimaryDataAsset_ClueConfig* Root);


#pragma region Events
	
	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnCollectedClue OnCollectedClue;
	
	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnClueSelected OnClueSelected;

	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnUpdateClueTree OnClueTrueCreated;

#pragma endregion

#pragma region Utility
		
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Clue System|Clue Manager|Utility")
	bool HasCollectedClue(UPrimaryDataAsset_Clue* ClueToCheck);

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
