// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


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
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System")
	UPrimaryDataAsset_Clue* ClueDataAsset;

	/**
	 * @brief The Additional Information to be accessed
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System")
	FString Information;
};

USTRUCT(BlueprintType)
struct FAreaClues
{
	GENERATED_BODY()

	FAreaClues()
	{
		CollectedClues.Empty();
	}

	FAreaClues(TMap<UPrimaryDataAsset_Clue*, bool> Clues)
	{
		CollectedClues = Clues;
	}
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Clue System")
	TMap<UPrimaryDataAsset_Clue*, bool> CollectedClues;
};

USTRUCT(BlueprintType)
struct FReplicatedAreaClues
{
	GENERATED_BODY()

	FReplicatedAreaClues()
	{
		AreaName = "";
		CollectedClues.Empty();
		bIsDirty = true;
	}

	FReplicatedAreaClues(FString Name, TArray<TWeakObjectPtr<UPrimaryDataAsset_Clue>> Clues)
	{
		AreaName = Name;
		CollectedClues = Clues;
		bIsDirty = true;
	}

	UPROPERTY(BlueprintReadOnly, Category="Clue System")
	bool bIsDirty;

	UPROPERTY(BlueprintReadOnly, Category="Clue System")
	TArray<int> DirtyIndices;
	
	UPROPERTY(BlueprintReadOnly, Category="Clue System")
	FString AreaName;	
 
	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimaryDataAsset_Clue>> CollectedClues;
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



	UPROPERTY(EditAnywhere, Category="Clue System")
	int NodeID;

	UPROPERTY(EditAnywhere, Category="Clue System")
	FString NodeName;

	UPROPERTY(EditAnywhere, Category="Clue System")
	TArray<UPrimaryDataAsset_ClueConfig*> ChildrenNodes;

	UPROPERTY(EditAnywhere, Category="Clue System")
	TArray<UPrimaryDataAsset_Clue*> Clues;
};
