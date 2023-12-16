
#include "Libraries/FGenericTree.h"
#include "Libraries/FTreeNode.h"

#include "GenericTreeStructure.h"

bool FGenericTree::AddChild(FTreeNode& ParentNode, FTreeNode& ChildNode)
{
	return ParentNode.AddChild(ChildNode);
}

void FGenericTree::RemoveChild(FTreeNode& ParentNode, FTreeNode& ChildNode)
{
}

void FGenericTree::AppendTree(FGenericTree& Tree, FTreeNode& ParentNode )
{
	if(!Nodes.Contains(ParentNode.GetID()))
	{
		UE_LOG(LogGenericTree, Error, TEXT("Parent Node [%s] does not exist in tree at Index [%d]!"), *ParentNode.ToString(), ParentNode.GetID());
		return;
	}

	if(AddChild(Nodes[ParentNode.GetID()], Tree.RootNode.GetMutable<FTreeNode>()))
	{
		TMap<int, FTreeNode> LocalNodes;
		GenerateTreeRecursive(Tree.RootNode, LocalNodes);
		
		Nodes.Append(LocalNodes);
	}
}

void FGenericTree::GenerateTree()
{
	GenerateTreeRecursive(RootNode, Nodes);
}

void FGenericTree::GenerateTreeRecursive(FInstancedStruct& Node, TMap<int, FTreeNode>& NodeMap)
{
	const int NodeID = GetNextNodeID();
	UE_LOG(LogGenericTree, Log, TEXT("Generating Node ID [%d]"), NodeID);

	const UScriptStruct* NodeStruct = Node.GetScriptStruct();
	
	if(!IsValid(NodeStruct))
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node is not a valid struct!"));
		return;
	}

	if(NodeStruct->IsChildOf(FGenericTree::StaticStruct()))
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node is Root of Another Tree! Appending"));
		AppendTree(Node.GetMutable<FGenericTree>(), Node.GetMutable<FTreeNode>());
		return;
	}
	
	if(!NodeStruct->IsChildOf(FTreeNode::StaticStruct()))
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node is not a valid tree node!"));
		return;
	}

	if(Node.GetMutable<FTreeNode>().GetID() > -1)
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node already has an ID!"));
		return;
	}
	
	FTreeNode& NodeRef = Node.GetMutable<FTreeNode>();
	
	if(NodeMap.Contains(NodeRef.GetID()))
	{
		UE_LOG(LogGenericTree, Error, TEXT("Node %s already exists in tree! Index [%d]"), *NodeRef.ToString(), NodeRef.GetID());
		return;
	}
	
	NodeRef.SetID(NodeID);
	NodeMap.Add(NodeID, NodeRef);
	UE_LOG(LogGenericTree, Log, TEXT("Generating tree for node [%s] at Index [%d]"), *NodeRef.ToString(), NodeID);
	
	for(FInstancedStruct& ChildNode : NodeRef.GetChildren())
	{
		FTreeNode& ChildNodeRef = ChildNode.GetMutable<FTreeNode>();
		UE_LOG(LogGenericTree, Log, TEXT("Generating tree for child node [%s] at Index [%d]"), *ChildNodeRef.ToString(), NodeID);
		ChildNodeRef.SetParent(Node);
		
		if(ChildNodeRef.GetChildren().Num() == 0)
		{
			UE_LOG(LogGenericTree, Log, TEXT("Child node %s is a leaf node"), *ChildNodeRef.ToString());
			const int ChildNodeID = GetNextNodeID();
			ChildNodeRef.SetID(ChildNodeID);
			NodeMap.Add(ChildNodeID, ChildNodeRef);
			UE_LOG(LogGenericTree, Log, TEXT("Child node %s at Index [%d]"), *ChildNodeRef.ToString(), ChildNodeID);
			continue;
		}

		GenerateTreeRecursive(ChildNode, NodeMap);
	}
}

int FGenericTree::GetNextNodeID()
{
	return Nodes.Num();
}
