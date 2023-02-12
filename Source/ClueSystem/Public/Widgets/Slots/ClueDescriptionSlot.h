// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ClueDescriptionSlot.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueDescriptionSlot : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void UpdateClueDescription(FString ClueDescription){TextBlock_ClueDescription->SetText(FText::FromString(ClueDescription));}

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextBlock_ClueDescription;
};
