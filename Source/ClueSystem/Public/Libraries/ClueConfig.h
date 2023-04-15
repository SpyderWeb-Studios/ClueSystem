#pragma once
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"


#include "ClueConfig.generated.h"

USTRUCT(BlueprintType)
struct FClueLocationConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UPrimaryDataAsset_ClueConfig> RootNode;
};
