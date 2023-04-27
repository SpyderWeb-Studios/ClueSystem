// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "GameFramework/ClueBase.h"

#include "Engine/StreamableManager.h"
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
	
	UClueManagerSubsystem* ClueManager = GetGameInstance()->GetSubsystem<UClueManagerSubsystem>();
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

