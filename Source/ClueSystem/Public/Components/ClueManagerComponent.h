// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Libraries/EventDelegateLibrary.h"
#include "ClueManagerComponent.generated.h"


class UPrimaryDataAsset_Clue;
struct FClueTreeNode;
struct FAreaClues;
class UPrimaryDataAsset_ClueConfig;

/**
 * 
 */
UCLASS( ClassGroup=(Clue), BlueprintType, meta=(BlueprintSpawnableComponent) )
class CLUESYSTEM_API UClueManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClueManagerComponent();
void Cleanup();
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Clue System|Clue Manager|Setup")
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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Clue System|Clue Manager")
    TMap<FString, FAreaClues> CollectedClues;
	
	// Tree Structure
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Clue System|Clue Manager")
	TMap<int, FClueTreeNode> ClueConfigTree;


		
};
