// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "ClueTypeImage.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueTypeImage : public UPrimaryDataAsset_Clue
{
	GENERATED_BODY()


	
#pragma region Image
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TObjectPtr<UTexture2D> ClueImage;
	
#pragma endregion

public:


	virtual bool ViewClue(UPanelWidget* ClueSwitcherSlot) override;
	
	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<UTexture2D> GetClueImage() const {return ClueImage;}
};
