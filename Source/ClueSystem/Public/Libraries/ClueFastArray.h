#pragma once

#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "Engine/NetSerialization.h"
#include "UObject/Class.h"
#include "ClueFastArray.generated.h"

/** Step 1: Make your struct inherit from FFastArraySerializerItem */
USTRUCT()
struct FReplicatedClueItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FReplicatedClueItem()
	{
		AreaName = "";
	}
 
	// Your data:
	UPROPERTY()
	FString AreaName;	
 
	UPROPERTY()
	TArray<TWeakObjectPtr<UPrimaryDataAsset_Clue>> CollectedClues;
 
	/** 
	 * Optional functions you can implement for client side notification of changes to items; 
	 * Parameter type can match the type passed as the 2nd template parameter in associated call to FastArrayDeltaSerialize
	 * 
	 * NOTE: It is not safe to modify the contents of the array serializer within these functions, nor to rely on the contents of the array 
	 * being entirely up-to-date as these functions are called on items individually as they are updated, and so may be called in the middle of a mass update.
	 */
	void PreReplicatedRemove(const struct FReplicatedAreaClueArray& InArraySerializer);
	void PostReplicatedAdd(const struct FReplicatedAreaClueArray& InArraySerializer);
	void PostReplicatedChange(const struct FReplicatedAreaClueArray& InArraySerializer);
	
	bool operator==(const FReplicatedClueItem& Other) const
	{
		return this->AreaName == Other.AreaName;
	}
	
	friend uint32 GetTypeHash(const FReplicatedClueItem& other)
	{
		return GetTypeHash(other.ReplicationID);
	}
};
 
/** Step 2: You MUST wrap your TArray in another struct that inherits from FFastArraySerializer */
USTRUCT()
struct FReplicatedAreaClueArray: public FFastArraySerializer
{
	GENERATED_BODY()
 
	UPROPERTY()
	TArray<FReplicatedClueItem>	Items;	/** Step 3: You MUST have a TArray named Items of the struct you made in step 1. */
 
	/** Step 4: Copy this, replace example with your names */
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParams)
	{
	   return FFastArraySerializer::FastArrayDeltaSerialize<FReplicatedClueItem, FReplicatedAreaClueArray>( Items, DeltaParams, *this );
	}
};
 
/** Step 5: Copy and paste this struct trait, replacing FExampleArray with your Step 2 struct. */
template<>
struct TStructOpsTypeTraits< FReplicatedAreaClueArray > : public TStructOpsTypeTraitsBase2<FReplicatedAreaClueArray>
{
       enum 
       {
			WithNetDeltaSerializer = true,
       };
};