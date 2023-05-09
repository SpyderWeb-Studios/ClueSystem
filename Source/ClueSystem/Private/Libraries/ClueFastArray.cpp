#include "Libraries/ClueFastArray.h"


void FReplicatedClueItem::PreReplicatedRemove(const FReplicatedAreaClueArray& InArraySerializer)
{
	UDebugFunctionLibrary::DebugLog( "PreReplicatedRemove: " + AreaName);
}

void FReplicatedClueItem::PostReplicatedAdd(const FReplicatedAreaClueArray& InArraySerializer)
{
	UDebugFunctionLibrary::DebugLog("PostReplicatedAdd: " + AreaName);
}

void FReplicatedClueItem::PostReplicatedChange(const FReplicatedAreaClueArray& InArraySerializer)
{
	UDebugFunctionLibrary::DebugLog("PostReplicatedChange: " + AreaName);
}
