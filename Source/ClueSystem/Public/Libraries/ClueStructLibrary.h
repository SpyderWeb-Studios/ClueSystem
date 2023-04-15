#pragma once
#include "CoreMinimal.h"
#include "ClueStructLibrary.generated.h"


class UPrimaryDataAsset_ClueConfig;
class UPrimaryDataAsset_Clue;

USTRUCT(BlueprintType)
struct FAdditionalClueInfo
{
	GENERATED_BODY()

	/**
	 * @brief The Data Asset necessary for this information to be available
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UPrimaryDataAsset_Clue* ClueDataAsset;

	/**
	 * @brief The Additional Information to be accessed
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Information;
};

USTRUCT(BlueprintType)
struct FAreaClues
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<UPrimaryDataAsset_Clue*, bool> CollectedClues;
};

USTRUCT(BlueprintType)
struct FClueTreeNode
{
	GENERATED_BODY()

	// Needs
	// - Node ID
	// - Children Nodes (Array of Clue Config Data Assets)

	FClueTreeNode()
	{
		NodeID = -1;
	}

	FClueTreeNode(int ID)
	{
		NodeID = ID;
	}

	FClueTreeNode(int ID, TArray<UPrimaryDataAsset_ClueConfig*> Children)
	{
		NodeID = ID;
		ChildrenNodes = Children;
	}

	FClueTreeNode(int ID, TArray<UPrimaryDataAsset_Clue*> ClueList)
	{
		NodeID = ID;
		Clues = ClueList;
	}

	FClueTreeNode(int ID, TArray<UPrimaryDataAsset_ClueConfig*> Children, TArray<UPrimaryDataAsset_Clue*> ClueList)
	{
		NodeID = ID;
		ChildrenNodes = Children;
		Clues = ClueList;
	}

	FClueTreeNode(int ID, TObjectPtr<UPrimaryDataAsset_ClueConfig> Child)
	{
		NodeID = ID;
		ChildrenNodes.Add(Child);
	}
	
	FClueTreeNode(int ID, TObjectPtr<UPrimaryDataAsset_Clue> Clue)
	{
		NodeID = ID;
		Clues.Add(Clue);
	}

	int FindChildRelativeIndex(const UPrimaryDataAsset_ClueConfig* Child);

	int FindChildRelativeIndex(const UPrimaryDataAsset_Clue* Child);



	UPROPERTY(EditDefaultsOnly)
	int NodeID;

	UPROPERTY(EditDefaultsOnly)
	FString NodeName;

	UPROPERTY(EditDefaultsOnly)
	TArray<UPrimaryDataAsset_ClueConfig*> ChildrenNodes;

	UPROPERTY(EditDefaultsOnly)
	TArray<UPrimaryDataAsset_Clue*> Clues;
};
