#pragma once
#include "Enums/EClueLocation.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "ClueConfig.generated.h"

USTRUCT(BlueprintType)
struct FClueLocationConfig
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<EClueLocation> ClueLocation; 
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<UPrimaryDataAsset_Clue*> Clues;
	
	bool operator==(const FClueLocationConfig& Other) const
	{
		return ClueLocation==Other.ClueLocation;
	}


	void UpdateClueIndices(EClueLocation Location);
	

};


inline void FClueLocationConfig::UpdateClueIndices(EClueLocation Location)
{
    ClueLocation = Location;
	for(int	i = 0; i < Clues.Num(); i++)
	{
		if(!Clues[i]) continue;
		Clues[i]->SetClueIndex(i);
		Clues[i]->SetClueLocation(ClueLocation);
		
	}
}
