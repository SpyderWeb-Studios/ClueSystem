// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "GameFramework/ClueBase.h"

#include "Components/ClueManagerComponent.h"
#include "Engine/StreamableManager.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/ClueManagerSubsystem.h"

// Sets default values
AClueBase::AClueBase()
{
}

bool AClueBase::AttemptInteractionWithClue()
{
	if(GetNetMode() >= NM_Client)
	{
		UE_LOG(LogNet, Error, TEXT("AttemptInteractionWithClue called on Client"));
		return false;
	}
	
	
	UE_LOG(LogBlueprint, Display, TEXT("Clue Interacting"));
	
	FStreamableManager StreamableManager;
    
	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(ClueDataAsset.ToSoftObjectPath(),
	FStreamableDelegate::CreateUObject(this, &AClueBase::OnDataAssetLoaded), 0, false);
	
	return true;
}

bool AClueBase::AttemptInteractionWithClueManager(UPlayerClueManagerComponent* ClueManager)
{
	if(GetNetMode() >= NM_Client)
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "AttemptInteractionWithClueManager called on Client");
		return false;
	}

	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Interacting");

	TWeakObjectPtr<UPrimaryDataAsset_Clue> clue =  ClueDataAsset.LoadSynchronous();

	if(clue.IsValid() && IsValid(ClueManager))
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Successfully Collected");
		if(ClueManager->CollectClueLocally(clue.Get()))
		{
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void AClueBase::BeginPlay()
{
	Super::BeginPlay();
}

void AClueBase::OnDataAssetLoaded_Implementation()
{
	if(GetNetMode() >= NM_Client)
	{
		UE_LOG(LogNet, Error, TEXT("OnDataAssetLoaded_Implementation called on Client"));
		return;
	}
	
	UE_LOG(LogBlueprint, Display, TEXT("Clue Data Asset Loaded"));
 
 	// Get the Clue Data Asset and Validate it before sending it to the Clue Manager
 	UPrimaryDataAsset_Clue* ClueData = Cast<UPrimaryDataAsset_Clue>(ClueDataAsset.Get());
 	if(!IsValid(ClueData)) return;
 
 	// Log the Clue Data Asset
 	UE_LOG(LogBlueprint, Display, TEXT("Clue Data Asset: %s"), *GetNameSafe(ClueData));
 	
 	SendToClueManager(ClueData);
}

void AClueBase::SendToClueManager(UPrimaryDataAsset_Clue* Clue)
{
	if(GetNetMode() >= NM_Client)
	{
		UE_LOG(LogNet, Error, TEXT("SendToClueManager called on Client"));
		return;
	}


	UClueManagerComponent* ClueManager = Cast<UClueManagerComponent>(UGameplayStatics::GetGameMode(this)->GetComponentByClass(UClueManagerComponent::StaticClass()));
	
	// UClueManagerSubsystem* ClueManager = GetWorld()->GetSubsystem<UClueManagerSubsystem>();
	if(!ClueManager)
	{
		// Log Error
		UE_LOG(LogBlueprint, Error, TEXT("Clue Manager Subsystem Not Found"));
		return;
	}
	if(ClueManager->CollectClue(Clue))
	{
		// Log Success
		UE_LOG(LogBlueprint, Display, TEXT("Clue Collected, Destroying Actor"));
		Destroy();
	}
}

