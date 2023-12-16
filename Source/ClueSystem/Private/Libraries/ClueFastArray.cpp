#include "Libraries/ClueFastArray.h"

#include "Macros.h"


void FReplicatedClueItem::PreReplicatedRemove(const FReplicatedAreaClueArray& InArraySerializer)
{
//	UDebugFunctionLibrary::DebugLog( "PreReplicatedRemove: " + AreaName);
}

void FReplicatedClueItem::PostReplicatedAdd(const FReplicatedAreaClueArray& InArraySerializer)
{
//	UDebugFunctionLibrary::DebugLog("PostReplicatedAdd: " + AreaName);
//	UDebugFunctionLibrary::DebugLog("PostReplicatedAdd: " + FString::FromInt(CollectedClues.Num()));

	InArraySerializer.OnClueAddReplicated.Broadcast(*this);

}

void FReplicatedClueItem::PostReplicatedChange(const FReplicatedAreaClueArray& InArraySerializer)
{
//	UDebugFunctionLibrary::DebugLog("PostReplicatedChange: " + AreaName);
}
