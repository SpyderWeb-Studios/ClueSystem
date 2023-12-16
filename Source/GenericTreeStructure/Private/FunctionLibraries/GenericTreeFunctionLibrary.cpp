// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GenericTreeFunctionLibrary.h"

#include "Libraries/FGenericTree.h"

void UGenericTreeFunctionLibrary::GenerateTree(FGenericTree& Tree)
{
    Tree.GenerateTree();
}

TMap<int, FTreeNode> UGenericTreeFunctionLibrary::GetNodes(FGenericTree& Tree)
{
    return Tree.GetNodes();
}

void UGenericTreeFunctionLibrary::AppendTree(FGenericTree& SourceTree, FGenericTree& TreeToAppend, FTreeNode& ParentNode)
{
    SourceTree.AppendTree(TreeToAppend, ParentNode);
}