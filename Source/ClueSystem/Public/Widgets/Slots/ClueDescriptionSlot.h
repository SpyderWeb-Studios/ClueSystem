// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ClueDescriptionSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CLUESYSTEM_API UClueDescriptionSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	 * @brief Updates the Text of the Clue Description
	 * @param ClueDescription The Description of the Clue
	 */
	UFUNCTION(BlueprintCallable, Category="Clue System|Description")
	void UpdateClueDescription(FString ClueDescription){TextBlock_ClueDescription->SetText(FText::FromString(ClueDescription));}

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="Clue System|Description")
	UTextBlock* TextBlock_ClueDescription;
};
