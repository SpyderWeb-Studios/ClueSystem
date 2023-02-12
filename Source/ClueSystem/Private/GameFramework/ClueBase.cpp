// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ClueBase.h"

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
	OnDataAssetLoaded.AddUniqueDynamic(this, &AClueBase::SendToClueManager);
}

void AClueBase::SendToClueManager(UPrimaryDataAsset_Clue* Clue)
{
	UClueManagerSubsystem* ClueManager = GetGameInstance()->GetSubsystem<UClueManagerSubsystem>();
	if(!ClueManager) return;
	if(ClueManager->CollectClue(Clue)) Destroy();
}

