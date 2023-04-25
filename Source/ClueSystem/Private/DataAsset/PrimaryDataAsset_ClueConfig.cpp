// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "DataAsset/PrimaryDataAsset_ClueConfig.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/ClueManagerSubsystem.h"


void UPrimaryDataAsset_ClueConfig::UpdateClueIndices(FString Location)
{
	ClueLocation = Location;
	for(int	i = 0; i < Clues.Num(); i++)
	{
		if(!Clues[i]) continue;
		Clues[i]->SetClueIndex(i);
		Clues[i]->SetClueLocation(ClueLocation);
		
	}
}

FClueTree UPrimaryDataAsset_ClueConfig::GetClueTree() const
{
	if(!IsValid(UGameplayStatics::GetGameInstance(this))) return FClueTree();
	if(!IsValid(UGameplayStatics::GetGameInstance(this)->GetSubsystem<UClueManagerSubsystem>())) return FClueTree();
		
	return UGameplayStatics::GetGameInstance(this)->GetSubsystem<UClueManagerSubsystem>()->GetClueTree();
}
