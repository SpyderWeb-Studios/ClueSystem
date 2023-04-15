// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ClueBase.h"

#include "Engine/StreamableManager.h"
#include "Subsystems/ClueManagerSubsystem.h"

// Sets default values
AClueBase::AClueBase()
{
}

bool AClueBase::AttemptInteractionWithClue()
{
	UE_LOG(LogBlueprint, Display, TEXT("Clue Interacting"));
	LoadClueAssetData();
	return true;
}

// Called when the game starts or when spawned
void AClueBase::BeginPlay()
{
	Super::BeginPlay();
}

void AClueBase::OnDataAssetLoaded()
{
	UE_LOG(LogBlueprint, Display, TEXT("Clue Data Asset Loaded"));

	// Get the Clue Data Asset and Validate it before sending it to the Clue Manager
	UPrimaryDataAsset_Clue* ClueData = Cast<UPrimaryDataAsset_Clue>(ClueDataAsset.Get());
	if(!IsValid(ClueData)) return;

	// Log the Clue Data Asset
	UE_LOG(LogBlueprint, Display, TEXT("Clue Data Asset: %s"), *GetNameSafe(ClueData));
	
	SendToClueManager(ClueData);
}

void AClueBase::LoadClueAssetData_Implementation()
{
	FStreamableManager StreamableManager;
    
	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(ClueDataAsset.ToSoftObjectPath(),
	FStreamableDelegate::CreateUObject(this, &AClueBase::OnDataAssetLoaded), 0, false);
}

void AClueBase::SendToClueManager(UPrimaryDataAsset_Clue* Clue)
{
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

