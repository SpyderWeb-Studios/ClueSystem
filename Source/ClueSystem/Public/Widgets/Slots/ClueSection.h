// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClueSlot.h"
#include "Blueprint/UserWidget.h"
#include "ClueSection.generated.h"


class UPrimaryDataAsset_Clue;
/**
 *
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueSection : public UUserWidget
{
	GENERATED_BODY()
public:

	void UpdateSection(UPrimaryDataAsset_Clue* ClueDataAsset);

	void SetSectionSize(int SectionSize);

	int GetSectionSize() const {return SlotArray.Num();}

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UClueSlot> ClueSlotClass;

	TMap<FString, UClueSlot*> Slots;

	TArray<UClueSlot*> SlotArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget))
	UPanelWidget* SectionPanel;
};
