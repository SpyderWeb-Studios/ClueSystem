// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ClueManagerSubsystem.h"

#include "ClueSystem.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"


UClueManagerSubsystem::UClueManagerSubsystem()
{
}

void UClueManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

bool UClueManagerSubsystem::CollectClue(UPrimaryDataAsset_Clue* Clue)
{
	UE_LOG(LogClue, Display, TEXT("Attempting to Collect Clue"));
	
	if(!Clue->IsValidLowLevel()) return false;
	
	UE_LOG(LogClue, Display, TEXT("Collecting Clue: %s"), *Clue->GetClueName());
	FAreaClues AreaClues;
	
	// If the Map has the Enum already, then we need to save a reference to the current value
	if(CollectedClues.Contains(Clue->GetClueLocation()))
	{
	// If the Map has the Enum already, then we need to save a reference to the current value
		AreaClues = CollectedClues[Clue->GetClueLocation()];
		
		UE_LOG(LogClue, Display, TEXT("Clue Location already in Map"));
	}

	// If it already exists then Return False
	if(AreaClues.CollectedClues.Contains(Clue)) return false;

	UE_LOG(LogClue, Display, TEXT("Clue doesn't already exist in Map"), *Clue->GetClueName());
	
	AreaClues.CollectedClues.Add(Clue, true);
	CollectedClues.Add(Clue->GetClueLocation(), AreaClues);
	
	UE_LOG(LogClue, Display, TEXT("Clue Successfully Added"), *Clue->GetClueName());

	OnCollectedClue.Broadcast(Clue);
	
	return true;
}

void UClueManagerSubsystem::SetClueConfigRoot(const FClueLocationConfig& Root)
{
	// Iterate through the Root and recursively add the children to the Map
	ClueConfigRoot = Root;
}

void UClueManagerSubsystem::BroadcastNumberOfClues()
{
	for(auto& clue : NumberOfCluesInLocations)
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Broadcast Clue Location", EDebuggingType::DT_Log);
		OnUpdateClueSectionSize.Broadcast(clue.Key, clue.Value);
	}
}

bool UClueManagerSubsystem::HasCollectedClue(UPrimaryDataAsset_Clue* ClueToCheck)
{

	if(!ClueToCheck) return false;
	
	if(CollectedClues.Contains(ClueToCheck->GetClueLocation()))
	{
		return CollectedClues[ClueToCheck->GetClueLocation()].CollectedClues.Contains(ClueToCheck);
	}

	return false;
}
