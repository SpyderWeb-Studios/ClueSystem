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

	FClueTreeNode()
	{
		NodeID = -1;
	}

	FClueTreeNode(int Node, TSoftObjectPtr<UPrimaryDataAsset_Clue> Clue, TArray<TSoftObjectPtr<UPrimaryDataAsset_ClueConfig>> Branches)
	{
		NodeID = Node;
		ClueDataPoint = Clue;
		this->Branches = Branches;
	}

	FClueTreeNode(int Node, UPrimaryDataAsset_Clue* Clue)
	{
		NodeID = Node;
		ClueDataPoint = Clue;
	}
	
	UPROPERTY(BlueprintReadOnly)
	int NodeID;

	// The Clue that is associated with this Node
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UPrimaryDataAsset_Clue> ClueDataPoint;

	// The Branches that are associated with this Node
	UPROPERTY(BlueprintReadOnly)
	TArray<TSoftObjectPtr<UPrimaryDataAsset_ClueConfig>> Branches;
};
