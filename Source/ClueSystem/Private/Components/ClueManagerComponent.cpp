// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ClueManagerComponent.h"

#include "ClueSystem.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"



void UClueManagerComponent::Cleanup()
{
	ClueConfigTree.Empty();
 	CollectedClues.Empty();
 	ClueConfigRoot = nullptr;

	OnClueSelected.Clear();
	OnCollectedClue.Clear();
	OnClueTrueCreated.Clear();
	
}

bool UClueManagerComponent::CollectClue(UPrimaryDataAsset_Clue* Clue)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Attempting to Collect Clue");
	
	if(!IsValid(Clue)) return false;
	
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Collecting Clue: " +Clue->GetClueName());
	FAreaClues AreaClues;
	
	// If the Map has the Enum already, then we need to save a reference to the current value
	if(CollectedClues.Contains(Clue->GetClueLocation()))
	{
	// If the Map has the Enum already, then we need to save a reference to the current value
		AreaClues = CollectedClues[Clue->GetClueLocation()];
		
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Location already in Map");
	}

	// If it already exists then Return False
	if(AreaClues.CollectedClues.Contains(Clue)) return false;

	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue doesn't already exist in Map" +Clue->GetClueName());
	
	AreaClues.CollectedClues.Add(Clue, true);
	CollectedClues.Add(Clue->GetClueLocation(), AreaClues);
	
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Successfully Added" +Clue->GetClueName());

	OnCollectedClue.Broadcast(Clue);
	
	return true;
}


void UClueManagerComponent::SetClueConfigRoot(UPrimaryDataAsset_ClueConfig* Root)
{
	// Iterate through the Root and recursively add the children to the Map
	ClueConfigRoot = Root;

	// RecursiveCreateTree(ClueConfigRoot, ClueConfigTree);
	CreateTreeRecursively(Root, ClueConfigTree);

	// Iterate through the Map and Log the Tree
	for(const auto& node : ClueConfigTree)
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Node: ["+FString::FromInt(node.Key)+"] with Name: ["+node.Value.NodeName+"]");
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Branches: ["+ FString::FromInt(node.Value.ChildrenNodes.Num())+"]");
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clues: ["+FString::FromInt(node.Value.Clues.Num())+"])");
	}

	OnClueTrueCreated.Broadcast(FClueTree(ClueConfigTree));
	
}

bool UClueManagerComponent::HasCollectedClue(UPrimaryDataAsset_Clue* ClueToCheck)
{

	if(!ClueToCheck) return false;
	
	if(CollectedClues.Contains(ClueToCheck->GetClueLocation()))
	{
		return CollectedClues[ClueToCheck->GetClueLocation()].CollectedClues.Contains(ClueToCheck);
	}

	return false;
}

int UClueManagerComponent::GetIndexFromName(FString ClueName) const
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

int UClueManagerComponent::GetParentIndexFromIndex(int Index) const
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

int UClueManagerComponent::GetParentIndexFromName(FString ClueName) const
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

TMap<int, FClueTreeNode> UClueManagerComponent::GetClueTree() const
{
	return ClueConfigTree;
}


void UClueManagerComponent::CreateTreeRecursively(UPrimaryDataAsset_ClueConfig* Config,
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
			UDebugFunctionLibrary::DebugLogWithObjectContext(this,"Clue is not valid");
			continue;
		}
		
		if(child->GetClueIndex() > 0 && Tree.Contains(child->GetClueIndex()))
		{
			// Log Warning
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, FString::Printf(TEXT("Clue [%s] already exists in Tree. Clue Index: [%d]"), *child->GetClueName(), child->GetClueIndex()));
		}
		
		FClueTreeNode ChildNode = FClueTreeNode(Tree.Num());
		ChildNode.NodeName = child->GetClueName();
		child->SetClueIndex(Tree.Num());
		child->SetClueLocation(Config->GetClueLocation());
		
		Tree.Add(Tree.Num(), ChildNode);
	}

	// Iterate through Children Nodes and Set their Node ID
	for(const auto& child : Config->GetBranches())
	{
		// Validate Child and Log Error if not valid
		if(!IsValid(child))
		{
			// log error
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Branch is not valid");
			continue;
		}
		if(child->GetIndex() > 0 && Tree.Contains(child->GetIndex()))
		{
			// Log Warning
			UDebugFunctionLibrary::DebugLogWithObjectContext(this,"Branch ["+child->GetClueLocation()+"] already exists in Tree. Branch Index: ["+FString::FromInt(child->GetIndex())+"]");
			
			continue;
		}
		
		CreateTreeRecursively(child, Tree);
	}

}

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerComponent::GetClueConfigFromIndex(int Index) const
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

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerComponent::GetClueConfigFromName(FString ClueName) const
{
	return GetClueConfigFromIndex(ClueConfigTree[GetIndexFromName(ClueName)].NodeID);
}

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerComponent::GetClueConfigFromParentIndex(int ParentIndex, FString ClueLocation) const
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

TSoftObjectPtr<UPrimaryDataAsset_ClueConfig> UClueManagerComponent::GetClueConfigFromParentName(
	FString ParentName, FString ClueLocation) const
{
	return GetClueConfigFromParentIndex(GetIndexFromName(ParentName), ClueLocation);
}

TArray<UPrimaryDataAsset_Clue*> UClueManagerComponent::GetCollectedClues()
{
	TArray<UPrimaryDataAsset_Clue*> Collected;

	for(const auto& collectedClue : CollectedClues)
	{
		TArray<UPrimaryDataAsset_Clue*> temp;
		collectedClue.Value.CollectedClues.GetKeys(temp);
		Collected.Append(temp);
	}
	return Collected;
}
