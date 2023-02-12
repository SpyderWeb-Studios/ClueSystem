// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Libraries/EventDelegateLibrary.h"


#include "ClueBase.generated.h"

class UPrimaryDataAsset_Clue;


UCLASS()
class CLUESYSTEM_API AClueBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClueBase();

	UFUNCTION(BlueprintCallable)
	virtual bool AttemptInteractionWithClue();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TSoftObjectPtr<UPrimaryDataAsset_Clue> ClueDataAsset; 

	UPROPERTY(BlueprintCallable)
	FOnDataAssetLoaded OnDataAssetLoaded;

	UFUNCTION(BlueprintImplementableEvent)
	void LoadClueAssetData();

	UFUNCTION()
	void SendToClueManager(UPrimaryDataAsset_Clue* Clue);
};
