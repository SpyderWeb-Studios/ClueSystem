#include "Libraries/FTreeNode.h"

#include "MovieSceneSequenceID.h"

TArray<FInstancedStruct> FTreeNode::GetChildren()
{
	return Children;
}

TArray<FInstancedStruct> FTreeNode::GetLeafNodes()
{
	TArray<FInstancedStruct> LeafNodes;
	for (FInstancedStruct& Child : Children)
	{
	const int NumChildren = Child.GetMutable<FTreeNode>().GetChildren().Num();
		UE_LOG(LogGenericTree, Log, TEXT("Child node %s has %d children"), *Child.GetMutable<FTreeNode>().ToString(), NumChildren);
		if (NumChildren == 0)
		{
			LeafNodes.Add(Child);
		}
	}
	
	return LeafNodes;
}

FString FTreeNode::ToString() const
{
	return NodeName;
}

bool FTreeNode::AddChild(const FInstancedStruct& RootNode)
{
	if(!RootNode.GetScriptStruct()->IsChildOf(FTreeNode::StaticStruct()))
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node is not a valid tree node!"));
		return false;
	}

	return Children.Add(RootNode) >= 0;
}

bool FTreeNode::AddChild(const FTreeNode& RootNode)
{
	const FInstancedStruct Node = FInstancedStruct::Make(RootNode);

	if(!Node.IsValid())
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node is not a valid struct!"));
		return false;
	}
	
	return AddChild(Node);
}
