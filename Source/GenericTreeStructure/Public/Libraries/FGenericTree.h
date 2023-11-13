#pragma once

#include "CoreMinimal.h"
#include "FTreeNode.h"
#include "FGenericTree.generated.h"

USTRUCT(BlueprintType)
struct FGenericTree
{
	GENERATED_BODY()
	
	FTreeNode RootNode;

	void AddChild(FTreeNode& ParentNode, FTreeNode& ChildNode);

	void RemoveChild(FTreeNode& ParentNode, FTreeNode& ChildNode);

	void GenerateTree();
	
	void GenerateTreeRecursive(FTreeNode& Node);
	
};
