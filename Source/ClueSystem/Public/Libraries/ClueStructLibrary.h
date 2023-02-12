#pragma once


#include "ClueStructLibrary.generated.h"


class UPrimaryDataAsset_Clue;

USTRUCT(BlueprintType)
struct FAdditionalClueInfo
{
	GENERATED_BODY()

	/**
	 * @brief The Data Asset necessary for this information to be available
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UPrimaryDataAsset_Clue* ClueDataAsset;

	/**
	 * @brief The Additional Information to be accessed
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Information;
};

USTRUCT(BlueprintType)
struct FAreaClues
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<UPrimaryDataAsset_Clue*, bool> CollectedClues;
};

