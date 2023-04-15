// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClueSlot.h"
#include "Blueprint/UserWidget.h"
#include "ClueSection.generated.h"


class UPrimaryDataAsset_ClueConfig;
/**
 *
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueSection : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetSectionSize(int SectionSize);

	int GetSectionSize() const {return SlotArray.Num();}
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LoadBranch();

	UFUNCTION(BlueprintCallable)
	void SetBranch(TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> Branch) {SectionBranch = Branch;}
	
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UClueSlot> ClueSlotClass;

	TMap<FString, UClueSlot*> Slots;

	TArray<UClueSlot*> SlotArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget))
	UPanelWidget* SectionPanel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> SectionBranch;

	UFUNCTION(BlueprintNativeEvent)
	void OnSectionBranchLoaded();
};
