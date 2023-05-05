#include "Libraries/ClueFastArray.h"


void FReplicatedClueItem::PreReplicatedRemove(const FReplicatedAreaClueArray& InArraySerializer)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(InArraySerializer.OwningObject, "PreReplicatedRemove: " + AreaName);
}

void FReplicatedClueItem::PostReplicatedAdd(const FReplicatedAreaClueArray& InArraySerializer)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(InArraySerializer.OwningObject, "PostReplicatedAdd: " + AreaName);
}

void FReplicatedClueItem::PostReplicatedChange(const FReplicatedAreaClueArray& InArraySerializer)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(InArraySerializer.OwningObject, "PostReplicatedChange: " + AreaName);
}
