// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericTreeFunctionLibrary.generated.h"

struct FTreeNode;
struct FGenericTree;
/**
 * 
 */
UCLASS()
class GENERICTREESTRUCTURE_API UGenericTreeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GenericTree")
	static void GenerateTree(UPARAM(ref) FGenericTree& Tree);
	
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GenericTree")
	static TMap<int, FTreeNode> GetNodes(UPARAM(ref) FGenericTree& Tree);

	/**
	 * @brief Appends the tree to the source tree
	 * @param SourceTree The Tree to append to
	 * @param TreeToAppend The Tree to copy from
	 */
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "GenericTree")
	static void AppendTree(UPARAM(ref) FGenericTree& SourceTree, UPARAM(ref) FGenericTree& TreeToAppend, UPARAM(ref) FTreeNode& ParentNode);
};
