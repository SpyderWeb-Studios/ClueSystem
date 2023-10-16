// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Libraries/ClueFastArray.h"
#include "Libraries/ClueStructLibrary.h"
#include "Libraries/EventDelegateLibrary.h"

#include "Net/UnrealNetwork.h"

#include "PlayerClueManagerComponent.generated.h"

class UPrimaryDataAsset_Clue;

UCLASS(ClassGroup=("Clue Management"), meta=(BlueprintSpawnableComponent) )
class CLUESYSTEM_API UPlayerClueManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerClueManagerComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * @brief This variation of the Collect Clue Function will only work on the server, and will collect the
	 * clue only for the owning player.
	 * @param Clue The Clue to collect
	 * @return True if the clue was collected, false if not
	 */
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category="Clue Management")
	bool CollectClueLocally(UPrimaryDataAsset_Clue* Clue);

	UFUNCTION(BlueprintCallable, Category="Clue Management")
	bool HasCollectedClue(UPrimaryDataAsset_Clue* Clue);
	
	UFUNCTION()
	void OnClueAddReplicated(const FReplicatedClueItem& ClueItem);

	UPROPERTY(BlueprintAssignable, Category="Clue Manager|Events")
	FOnCollectedClue OnCollectedClueLocally;
	
	UPROPERTY(BlueprintAssignable, Category="Clue Manager|Events")
	FOnClueSelected OnClueSelectedLocally;


	UFUNCTION(BlueprintPure, Category = "Inventory")
	ULocalPlayer* GetLocalPlayerFromOwner() const {return OwningLocalPlayer.Get();}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetLocalPlayerFromOwner(APlayerController* PlayerController)
	{
		if(IsValid(PlayerController))
		{
			OwningLocalPlayer = PlayerController->GetLocalPlayer();
		}
	}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * @brief Server Only Map that stores the index for each Location in the Fast Array for
	 * easy updating of the clue system
	 */
	TMap<FString, int> CollectedClues;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Clue Management")
	FReplicatedAreaClueArray ReplicatedClues;


	UFUNCTION(Client, Reliable, BlueprintCallable, Category="Clue Management")
	void Client_SetupClueSubsystem();

	UFUNCTION(Server,Reliable, Category="Clue Management")
	void Server_SetupClueManager();

	UFUNCTION(BlueprintCallable)
	void OnGlobalClueCollected(UPrimaryDataAsset_Clue* Clue);
	
	TWeakObjectPtr<ULocalPlayer> OwningLocalPlayer;
};
