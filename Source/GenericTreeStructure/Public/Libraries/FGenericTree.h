#pragma once

#include "CoreMinimal.h"
#include "FTreeNode.h"
#include "InstancedStruct.h"
#include "FGenericTree.generated.h"


USTRUCT(BlueprintType)
struct FGenericTree
{
	GENERATED_BODY()

	FGenericTree()
	{
	}

	UPROPERTY(EditAnywhere, Category="Generic Tree", meta=(BaseStruct="/Script/GenericTreeStructure.TreeNode"))
	FInstancedStruct RootNode;

	bool AddChild(FTreeNode& ParentNode, FTreeNode& ChildNode);

	void RemoveChild(FTreeNode& ParentNode, FTreeNode& ChildNode);

	void AppendTree(FGenericTree& Tree, FTreeNode& ParentNode);
	
	void GenerateTree();
	
	void GenerateTreeRecursive(FInstancedStruct& Node, TMap<int, FTreeNode>& NodeMap);

	TMap<int, FTreeNode> GetNodes() {return Nodes;}
protected:

	int GetNextNodeID();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
 	TMap<int, FTreeNode> Nodes;
	
};
