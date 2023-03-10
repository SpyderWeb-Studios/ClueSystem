// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "Libraries/EventDelegateLibrary.h"
#include "ClueSlot.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void UpdateSlot(UPrimaryDataAsset_Clue* Clue);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ClueName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UButton> Button_ViewClue;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidgetOptional))
	TObjectPtr<UImage> Image_ClueIcon;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TSoftObjectPtr<UPrimaryDataAsset_Clue> ClueData;

protected:

	UFUNCTION(BlueprintCallable)
		void ViewClue();

	UFUNCTION(BlueprintImplementableEvent)
		void LoadData();

	UFUNCTION(BlueprintCallable)
		void OnDataLoaded(UPrimaryDataAsset_Clue* Clue);

	FOnDataAssetLoaded OnDataAssetLoaded;
};
