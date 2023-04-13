// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/PrimaryDataAsset_ClueConfig.h"



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
