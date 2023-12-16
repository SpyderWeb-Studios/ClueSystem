#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "FTreeNode.generated.h"

USTRUCT(BlueprintType)
struct FTreeNode
{
	GENERATED_BODY()

	FTreeNode()
	{
		
	}
	TArray<FInstancedStruct> GetChildren();
	
	TArray<FInstancedStruct> GetLeafNodes();

	void SetParent(FInstancedStruct& NewParent)
	{
		Parent = NewParent;
	}

	FString ToString() const;
	
	int GetID() const {return _NodeID;}
	
	void SetID(int NodeID) {_NodeID = NodeID;}

	bool AddChild(const FInstancedStruct& RootNode);

	bool AddChild(const FTreeNode& RootNode);

protected:
	UPROPERTY(EditAnywhere, Category="Generic Tree", meta=(BaseStruct="/Script/GenericTreeStructure.TreeNode"))
	TArray<FInstancedStruct> Children;

	UPROPERTY(VisibleAnywhere, Category="Generic Tree")
	FInstancedStruct Parent;

	UPROPERTY(VisibleAnywhere, Category="Generic Tree")
	int _NodeID = -1;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category="Generic Tree")
	FString NodeName;
#endif
};
