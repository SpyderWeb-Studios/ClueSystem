// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "Libraries/ClueStructLibrary.h"
#include "UObject/Object.h"
#include "EventDelegateLibrary.generated.h"

class AClueBase;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCollectedClue, UPrimaryDataAsset_Clue*, CollectedClue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClueSelected, UPrimaryDataAsset_Clue*, CollectedClue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateClueLocation, FAreaClues, CollectedLocationClue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateClueSectionSize, EClueLocation, ClueLocation, int, SectionSize);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataAssetLoaded, UPrimaryDataAsset_Clue*, Clue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClueImageLoaded, TSoftObjectPtr<UTexture2D>, ClueImage);








/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UEventDelegateLibrary : public UObject
{
	GENERATED_BODY()
};
