// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/EClueLocation.h"
#include "Widgets/Slots/ClueSection.h"
#include "Widgets/Slots/ClueSlot.h"
#include "ClueListManager.generated.h"

class UPrimaryDataAsset_Clue;
/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueListManager : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UClueSection> ClueSectionClass;

	/**
	 * @brief Handles updating the list of slots, including the size of the list and the contents of known clues
	 */
	UFUNCTION()
	void UpdateSlotList(UPrimaryDataAsset_Clue* CollectedClue);


	UFUNCTION()
	void UpdateSectionSize(const FString& ClueLocation, int SectionSize);

	UFUNCTION()
	void UpdateSectionTree(const FClueTree ClueTree);

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UClueSection*> CollectedClueSections;


	UFUNCTION(BlueprintCallable)
	void OnConfigLoaded();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> ClueConfig;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<int, FClueTreeNode> LocalClueTree;
	
	// Roadmap for this class
	// - Associate a Config Data Asset with this manager to determine the order of the sections
};
