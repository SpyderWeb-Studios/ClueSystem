// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ClueBranchBrush.h"

#include "ClueSystem.h"
#include "Components/ClueManagerComponent.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "GameFramework/ClueBase.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

class AGameMode;

bool AClueBranchBrush::RegisterCluesInRange()
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if(!IsValid(GameMode))
	{
		UE_LOG(LogClue, Error, TEXT("%S"), *UDebugFunctionLibrary::FormatDebug(this, "Game Mode is Invalid"));
		return false;
	}
	
	UActorComponent* ClueManager = GameMode->GetComponentByClass(UClueManagerComponent::StaticClass());
	if(!IsValid(ClueManager))
	{
		UE_LOG(LogClue, Error, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "Clue Manager Component is Invalid"));
		return false;
	}	

	UClueManagerComponent* ClueManagerComponent = Cast<UClueManagerComponent>(ClueManager);
	
	TArray<AActor*> Clues;
	GetOverlappingActors(Clues);


	if(Clues.Num() < 1)
	{
		UE_LOG(LogClue, Warning, TEXT("Number of Encompassing Clues is 0"));
		return false;
	}
	
	for(AActor* Clue : Clues)
	{
		if(!IsValid(Clue))
		{
			UE_LOG(LogClue, Warning, TEXT("Actor is Invalid"));
			continue;
		}

		if(!Clue->Implements<UClueObjectInterface>())
		{
			UE_LOG(LogClue, Warning, TEXT("Actor Does Not Implement Clue Object Interface"));
			continue;
		}

		UPrimaryDataAsset_Clue* DataAsset_Clue = IClueObjectInterface::Execute_GetClueDataAsset(Clue);
		
		if(!IsValid(DataAsset_Clue))
		{
			UE_LOG(LogClue, Warning, TEXT("ClueDataAsset is Invalid"));
			continue;
		}
		
		ConnectedConfig->AddClue(DataAsset_Clue);
	}
	
	return true;
}

void AClueBranchBrush::TestRegister()
{
	RegisterCluesInRange();
}
