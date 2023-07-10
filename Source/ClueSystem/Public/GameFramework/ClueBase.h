// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PlayerClueManagerComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ClueObjectInterface.h"
#include "Libraries/EventDelegateLibrary.h"
#include "ClueBase.generated.h"

class UPrimaryDataAsset_Clue;

/*
 * Base class for clues
 */
UCLASS()
class CLUESYSTEM_API AClueBase : public AActor, public IClueObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClueBase();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category="Clue System|Interaction")
	virtual bool AttemptInteractionWithClue();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category="Clue System|Interaction")
	virtual bool AttemptInteractionWithClueManager(UPlayerClueManagerComponent* ClueManager);

	virtual UPrimaryDataAsset_Clue* GetClueDataAsset_Implementation() override;


	virtual bool SetClueDataAsset_Implementation(UPrimaryDataAsset_Clue* NewClueDataAsset) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Clue System|Clue")
	TSoftObjectPtr<UPrimaryDataAsset_Clue> ClueDataAsset;
	

	UFUNCTION(BlueprintAuthorityOnly, BlueprintNativeEvent, Category="Clue System")
	void OnDataAssetLoaded();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category="Clue System")
	void SendToClueManager(UPrimaryDataAsset_Clue* Clue);
};

