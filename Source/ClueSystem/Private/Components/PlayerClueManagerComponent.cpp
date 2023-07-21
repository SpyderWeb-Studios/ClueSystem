// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerClueManagerComponent.h"

#include "ClueSystem.h"
#include "Engine/StreamableManager.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "Interfaces/PlayerClueInterface.h"
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

bool UPlayerClueManagerComponent::HasCollectedClue(UPrimaryDataAsset_Clue* Clue)
{
	if(!IsValid(Clue))
	{
		UE_LOG(LogClue, Error, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: Clue is not Valid"));
		return false;
	}
	
	UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: " + Clue->GetClueName()));
	// Check if the clue is in the fast array
	if(ReplicatedClues.Items.ContainsByPredicate([&](const FReplicatedClueItem& Item){return Item.AreaName == Clue->GetClueLocation();}))
	{
		UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: Clue is in Fast Array"));
		const int ClueIndex = ReplicatedClues.Items.IndexOfByPredicate([&](const FReplicatedClueItem& Item){return Item.AreaName == Clue->GetClueLocation();});
		
		if(ReplicatedClues.Items[ClueIndex].AreaName == Clue->GetClueLocation() && ReplicatedClues.Items[ClueIndex].CollectedClues.Contains(Clue))
		{
			UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: Clue is in Fast Array and is the same as the Clue Location"));
			return true;
		}
		else
		{
			if(ReplicatedClues.Items[ClueIndex].AreaName == Clue->GetClueLocation())
			{
				UE_LOG(LogClue, Warning, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: Clue is in Fast Array but is not the same as the Clue Location"));
			}
			else
			{
				UE_LOG(LogClue, Warning, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: Clue is in Fast Array but is not the same as the Clue Location"));
			}
		}
	}
	UE_LOG(LogClue, Error, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "HasCollectedClue: Clue is not in Fast Array"));
	return false;
}

void UPlayerClueManagerComponent::OnClueAddReplicated(const FReplicatedClueItem& ClueItem)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "OnClueAddReplicated");
	if(!IsValid(GetLocalPlayerFromOwner())) return;

	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "GetLocalPlayerFromOwner is Valid");
	
	UObject* clue = ClueItem.CollectedClues[ClueItem.CollectedClues.Num() - 1].Get();
	if(!ClueItem.CollectedClues[ClueItem.CollectedClues.Num() - 1].IsValid())
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue is not Valid");
		FStreamableManager StreamableManager;
		clue = StreamableManager.LoadSynchronous(ClueItem.CollectedClues[ClueItem.CollectedClues.Num() - 1].Get());

		
	}
	if(IsValid(clue))
    {
    	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue is Valid");
    }
    else
    {
    	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue is not Valid");
    	return;
    }
	
	if(clue->IsA(UPrimaryDataAsset_Clue::StaticClass()))
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue is a subclass of PrimaryDataAsset_Clue");
	}
	else
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue is not a PrimaryDataAsset_Clue");
		return;
	}
	
	UClueManagerSubsystem* ClueManagerSubsystem = GetLocalPlayerFromOwner()->GetSubsystem<UClueManagerSubsystem>();

	
	
	ClueManagerSubsystem->OnCollectedClue.Broadcast(Cast<UPrimaryDataAsset_Clue>(clue));
	
}


// Called when the game starts
void UPlayerClueManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// Client_SetupClueSubsystem();
	Server_SetupClueManager();
}

void UPlayerClueManagerComponent::OnGlobalClueCollected(UPrimaryDataAsset_Clue* Clue)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "OnGlobalClueCollected Called");
	
	if(CollectClueLocally(Clue))
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue ["+ Clue->GetClueName() + "] at Location ["+ Clue->GetClueLocation() +"] was Collected Locally");
	}
	else
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue ["+ Clue->GetClueName() + "] at Location ["+ Clue->GetClueLocation() +"] was not Collected Locally");
	}
	
}

void UPlayerClueManagerComponent::Server_SetupClueManager_Implementation()
{
	if(!IsValid(GetOwner())) return;

	// Check that the Owner implements the IClueManagerInterface
	if(GetOwner()->Implements<UPlayerClueInterface>())
	{
		UClueManagerComponent* ClueManagerComponent = IPlayerClueInterface::Execute_GetClueManager(GetOwner());
		if(IsValid(ClueManagerComponent))
		{
			ClueManagerComponent->OnCollectedClue.AddUniqueDynamic(this, &UPlayerClueManagerComponent::OnGlobalClueCollected);
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Component is Valid, OnCollectedClue Event was Bound");

			for(UPrimaryDataAsset_Clue* Collected: ClueManagerComponent->GetCollectedClues())
			{
				UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "Adding Collected: [" + GetNameSafe(Collected) +"]"));
				CollectClueLocally(Collected);
			}
		}
		else
		{
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Component is Invalid");
		}
	}
	else
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Owner does not implement IClueManagerInterface");
	}
}

void UPlayerClueManagerComponent::Client_SetupClueSubsystem_Implementation()
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Setting up Clue Subsystem");

	// Get the Local Player and the Clue Manager Subsystem
	if(!IsValid(GetLocalPlayerFromOwner()))
	{
		UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "Local Player is Invalid"));
		return;
	}

	UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "Local Player is Valid"));
	
	UClueManagerSubsystem* ClueManagerSubsystem = GetLocalPlayerFromOwner()->GetSubsystem<UClueManagerSubsystem>();
	if(IsValid(ClueManagerSubsystem))
	{
		UE_LOG(LogClue, Display, TEXT("%s"), *UDebugFunctionLibrary::FormatDebug(this, "Clue Manager Subsystem is Valid"));
		ClueManagerSubsystem->SetPlayerClueManagerComponent(this);
		ReplicatedClues.OnClueAddReplicated.AddUniqueDynamic(this, &UPlayerClueManagerComponent::OnClueAddReplicated);
	}
	else
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Subsystem is Invalid");
	}
}

	