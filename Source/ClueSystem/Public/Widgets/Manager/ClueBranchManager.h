// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClueBranchManager.generated.h"

class UPrimaryDataAsset_ClueConfig;
/**
 * This Class takes in a Clue Config and recursively creates a tree of Clue Branches and Clue Leaves to display to the player. 
 * It will add the Clue Branch Manager's for each Clue Config Branch.
 */
UCLASS()
class CLUESYSTEM_API UClueBranchManager : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "ClueSystem")
		TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> GetClueConfig() const { return ClueConfig.Get(); }

	UFUNCTION(BlueprintCallable, Category = "ClueSystem")
		void SetClueConfig(TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> NewClueConfig) { ClueConfig = NewClueConfig; }
	

protected:
	/**
	 * @brief The Main Panel to add the Child Clue Branches to.
	 */
	 UPROPERTY(BlueprintReadOnly, Category = "Clue Config", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UPanelWidget> ClueBranchesPanel;
	
	// The Clue Config that this Clue Branch Manager is displaying.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clue Config", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> ClueConfig;

	/**
	 * @brief The Event that is called when the Clue Config is loaded. This handles a majority of the procedural generation of the Clue Branches and Clue Leaves.
	 * This can be overridden in Blueprints to add additional functionality, or replace the functionality entirely.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "ClueSystem")
	void OnClueConfigLoaded() const;
	
	virtual void NativeConstruct() override;
};
