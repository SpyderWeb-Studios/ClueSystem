// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Libraries/EventDelegateLibrary.h"
#include "ClueBase.generated.h"

class UPrimaryDataAsset_Clue;

/*
 * Base class for clues
 */
UCLASS()
class CLUESYSTEM_API AClueBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClueBase();

	UFUNCTION(BlueprintCallable, Category="Clue System|Interaction")
	virtual bool AttemptInteractionWithClue();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Clue System|Clue")
	TSoftObjectPtr<UPrimaryDataAsset_Clue> ClueDataAsset; 

	UFUNCTION(BlueprintCallable, Category="Clue System")
	void OnDataAssetLoaded();

	UFUNCTION()
	void SendToClueManager(UPrimaryDataAsset_Clue* Clue);
};
