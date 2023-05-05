// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerClueManagerComponent.h"

#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

// Sets default values for this component's properties
UPlayerClueManagerComponent::UPlayerClueManagerComponent()
{
	SetIsReplicatedByDefault(true);
}

void UPlayerClueManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPlayerClueManagerComponent, ReplicatedClues);
}

bool UPlayerClueManagerComponent::CollectClueLocally(UPrimaryDataAsset_Clue* Clue)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Collecting Clue Locally");
	if(GetOwner()->HasAuthority() && IsValid(Clue)){
		

		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue ["+ Clue->GetClueName() + "] at Location ["+ Clue->GetClueLocation() +"] is Valid and Owner has Authority");
		
		if(CollectedClues.Contains(Clue->GetClueLocation()))
		{
			const int ClueIndex = *CollectedClues.Find(Clue->GetClueLocation());
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Index is Valid, Location should exist in Fast Array");
			if(ReplicatedClues.Items[ClueIndex].AreaName == Clue->GetClueLocation() && !ReplicatedClues.Items[ClueIndex].CollectedClues.Contains(Clue))
			{
				UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Index is Valid, Location exists in Fast Array amd is the same as the Clue Location");
				ReplicatedClues.Items[ClueIndex].CollectedClues.AddUnique(Clue);

				ReplicatedClues.MarkItemDirty(ReplicatedClues.Items[ClueIndex]);
				ReplicatedClues.Items[ClueIndex].PostReplicatedAdd(ReplicatedClues);
				
				return true;
			}
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Index is Valid, Location exists in Fast Array but is not the same as the Clue Location or the Clue already exists in the Fast Array");
		}
		else
		{
			// Otherwise, we need to add the clue to the fast array
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Index is Invalid, Location does not exist in Fast Array");
			// First we need to add the clue to the fast array

			FReplicatedClueItem ClueItem = FReplicatedClueItem();
			ClueItem.AreaName = Clue->GetClueLocation();
			ClueItem.CollectedClues.AddUnique(Clue);

			const int Index = ReplicatedClues.Items.AddUnique(ClueItem);
			
			ReplicatedClues.MarkItemDirty(ReplicatedClues.Items[Index]);
			ReplicatedClues.Items[Index].PostReplicatedAdd(ReplicatedClues);
			
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Index is Valid, Location successfully added to Fast Array");
			CollectedClues.Add(Clue->GetClueLocation(), Index);
			return true;
		}
	}
	
	return false;
}


// Called when the game starts
void UPlayerClueManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

	