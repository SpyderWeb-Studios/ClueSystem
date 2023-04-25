// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
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

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Slot")
	void UpdateSlot(UPrimaryDataAsset_Clue* Clue);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget), Category="Clue System")
	TObjectPtr<UTextBlock> TextBlock_ClueName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget), Category="Clue System")
	TObjectPtr<UButton> Button_ViewClue;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidgetOptional), Category="Clue System")
	TObjectPtr<UImage> Image_ClueIcon;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Clue System")
	TSoftObjectPtr<UPrimaryDataAsset_Clue> ClueData;

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Slot")
		void SetNodeID(int ID) {NodeID = ID;}

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Slot")
		int GetNodeID() const {return NodeID;}

protected:

	UFUNCTION(BlueprintCallable, Category="Clue System|Clue Slot")
		void ViewClue();
	
	UFUNCTION()
		void OnDataLoaded();

	UPROPERTY(BlueprintReadOnly, Category="Clue System")
	int NodeID;
};
