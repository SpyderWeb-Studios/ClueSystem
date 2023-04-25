// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "Engine/Texture2D.h"
#include "ClueTypeImage.generated.h"

/**
 * This is a Clue Type that contains an image, it extends the Clue Data Asset and displays an image in the Clue Widget 
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
	
	
	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	TSoftObjectPtr<UTexture2D> GetClueImage() const {return ClueImage;}
};
