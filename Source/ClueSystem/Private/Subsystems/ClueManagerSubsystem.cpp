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

	// RecursiveCreateTree(ClueConfigRoot, ClueConfigTree);
	CreateTreeRecursively(Root.RootNode, ClueConfigTree);

	// Iterate through the Map and Log the Tree
	for(const auto& node : ClueConfigTree)
	{
		UE_LOG(LogClue, Display, TEXT("Node: %d with Name: [%s]"), node.Key, *node.Value.NodeName);
		UE_LOG(LogClue, Display, TEXT("Branches: %d"), node.Value.ChildrenNodes.Num());
		UE_LOG(LogClue, Display, TEXT("Clues: %d"), node.Value.Clues.Num());
	}
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

void UClueManagerSubsystem::CreateTreeRecursively(UPrimaryDataAsset_ClueConfig* Config,
	TMap<int, FClueTreeNode>& Tree)
{
	if(!Config) return;
	Config->SetIndex(Tree.Num());

	FClueTreeNode Node = FClueTreeNode(Config->GetIndex(), Config->GetBranches(), Config->GetClues());
	Node.NodeName = Config->GetClueLocation();

	Tree.Add(Tree.Num(), Node);

	for(const auto& child : Config->GetClues())
	{
		if(!IsValid(child))
		{
			// log error
			UE_LOG(LogClue, Error, TEXT("Clue is not valid"));
			continue;
		}
		
		if(child->GetClueIndex() > 0 && Tree.Contains(child->GetClueIndex()))
		{
			// Log Warning
			UE_LOG(LogClue, Warning, TEXT("Clue [%s] already exists in Tree. Clue Index: [%d]"), *child->GetClueName(), child->GetClueIndex());
		}
		
		FClueTreeNode ChildNode = FClueTreeNode(Tree.Num(), child);
		ChildNode.NodeName = child->GetClueName();
		child->SetClueIndex(Tree.Num());
		
		Tree.Add(Tree.Num(), ChildNode);
	}

	// Iterate through Children Nodes and Set their Node ID
	for(const auto& child : Config->GetBranches())
	{
		// Validate Child and Log Error if not valid
		if(!IsValid(child))
		{
			// log error
			UE_LOG(LogClue, Error, TEXT("Branch is not valid"));
			continue;
		}
		if(child->GetIndex() > 0 && Tree.Contains(child->GetIndex()))
		{
			// Log Warning
			UE_LOG(LogClue, Warning, TEXT("Branch [%s] already exists in Tree. Branch Index: [%d]"), *child->GetClueLocation(), child->GetIndex());
			
			continue;
		}
		
		CreateTreeRecursively(child, Tree);
	}

}
