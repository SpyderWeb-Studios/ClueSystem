#include "Libraries/ClueStructLibrary.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"

int FClueTreeNode::FindChildRelativeIndex(const UPrimaryDataAsset_ClueConfig* Child)
{
	// Find the index of the child in the array
	for (int i = 0; i < ChildrenNodes.Num(); i++)
	{
		if (ChildrenNodes[i] == Child)
		{
			return ChildrenNodes[i]->GetIndex() - NodeID;
		}
	}

	return -1;
}

int FClueTreeNode::FindChildRelativeIndex(const UPrimaryDataAsset_Clue* Child)
{
	// Find the index of the child in the array
	for (int i = 0; i < Clues.Num(); i++)
	{
		if (Clues[i] == Child)
		{
			return Clues[i]->GetClueIndex() - NodeID;
		}
	}

	return -1;
}
