// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "Slots/ClueDescriptionSlot.h"
#include "ClueViewer.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueViewer : public UUserWidget
{
	GENERATED_BODY()

public:
	
virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClueSelected(UPrimaryDataAsset_Clue* CollectedClue);

	UFUNCTION(BlueprintCallable)
	void ResetViewer();
	
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TextBlock_ClueDescription;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget))
	UVerticalBox* VerticalBox_ClueSections;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UClueDescriptionSlot> ClueDescriptionClass;

private:

	
	
};
