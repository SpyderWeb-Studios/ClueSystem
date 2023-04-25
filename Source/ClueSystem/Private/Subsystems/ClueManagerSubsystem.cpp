// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ClueManagerSubsystem.h"

#include "ClueSystem.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
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

void UClueManagerSubsystem::UpdateNumberOfCluesInLocation(FString ParentBranch, FString location, int Number)
{	
	// Log the Parent Branch, and the location of the clue with the number of clues in that location
	UE_LOG(LogTemp, Warning, TEXT("Parent Branch: %s, Location: %s, Number: %d"), *ParentBranch, *location, Number);
	NumberOfCluesInLocations.Add(location, Number);
}


void UClueManagerSubsystem::SetClueConfigRoot(UPrimaryDataAsset_ClueConfig* Root)
{
	// Iterate through the Root and recursively add the children to the Map
	ClueConfigRoot = Root;

	// RecursiveCreateTree(ClueConfigRoot, ClueConfigTree);
	CreateTreeRecursively(Root, ClueConfigTree);

	// Iterate through the Map and Log the Tree
	for(const auto& node : ClueConfigTree)
	{
		UE_LOG(LogClue, Display, TEXT("Node: %d with Name: [%s]"), node.Key, *node.Value.NodeName);
		UE_LOG(LogClue, Display, TEXT("Branches: %d"), node.Value.ChildrenNodes.Num());
		UE_LOG(LogClue, Display, TEXT("Clues: %d"), node.Value.Clues.Num());
	}

	OnClueTrueCreated.Broadcast(FClueTree(ClueConfigTree));
	
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

int UClueManagerSubsystem::GetNumberOfCluesInLocation(FString Location) const
{
	// Recursively iterate through the Tree and count the number of Clues

	for(const auto& node : ClueConfigTree)
	{
		if(node.Value.NodeName == Location)
		{
			return node.Value.Clues.Num();
		}
	}

	return 0;
}

int UClueManagerSubsystem::GetNumberOfCollectedCluesInLocation(FString Location) const
{
	// Recursively iterate through the Tree and count the number of Clues

	if(!CollectedClues.Contains(Location)) return 0;
	
	return CollectedClues[Location].CollectedClues.Num();
}

int UClueManagerSubsystem::GetIndexFromName(FString ClueName) const
{
	// Iterate through the Tree and find the Node with the Name
	for(const auto& node : ClueConfigTree)
	{
		if(node.Value.NodeName == ClueName)
		{
			return node.Key;
		}
	}

	return -1;
}

int UClueManagerSubsystem::GetParentIndexFromIndex(int Index) const
{
	// Iterate through the Tree and find the Node with the Name
	for(const auto& node : ClueConfigTree)
	{
		if(node.Value.ChildrenNodes.ContainsByPredicate([Index](const UPrimaryDataAsset_ClueConfig* Child){return Child->GetIndex() == Index;})
			|| node.Value.Clues.ContainsByPredicate([Index](const UPrimaryDataAsset_Clue* Child){return Child->GetClueIndex() == Index;}))
		{
			return node.Key;
		}
	}

	return -1;
}

int UClueManagerSubsystem::GetParentIndexFromName(FString ClueName) const
{
	// Iterate through the Tree and find the Node with the Name
	for(const auto& node : ClueConfigTree)
	{
		if(node.Value.NodeName == ClueName)
		{
			return GetParentIndexFromIndex(node.Key);
		}
	}

	return -1;
}

TMap<int, FClueTreeNode> UClueManagerSubsystem::GetClueTree() const
{
	return ClueConfigTree;
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
		
		FClueTreeNode ChildNode = FClueTreeNode(Tree.Num());
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

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerSubsystem::GetClueConfigFromIndex(int Index) const
{
	if(ClueConfigTree.Contains(GetParentIndexFromIndex(Index)))
	{
		for(const auto& child : ClueConfigTree[GetParentIndexFromIndex(Index)].ChildrenNodes)
		{
			if(child->GetClueLocation() == ClueConfigTree[Index].NodeName)
			{
				return child;
			}
		}
	}

	return nullptr;
}

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerSubsystem::GetClueConfigFromName(FString ClueName) const
{
	return GetClueConfigFromIndex(ClueConfigTree[GetIndexFromName(ClueName)].NodeID);
}

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerSubsystem::GetClueConfigFromParentIndex(int ParentIndex, FString ClueLocation) const
{
	// Iterate through the Tree and find the Node with the Name
	for(const auto& node : ClueConfigTree)
	{
		if(node.Value.NodeName == ClueLocation)
		{
			return GetClueConfigFromIndex(node.Value.NodeID);
		}
	}

	return nullptr;
}

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerSubsystem::GetClueConfigFromParentName(
	FString ParentName, FString ClueLocation) const
{
	return GetClueConfigFromParentIndex(GetIndexFromName(ParentName), ClueLocation);
}
