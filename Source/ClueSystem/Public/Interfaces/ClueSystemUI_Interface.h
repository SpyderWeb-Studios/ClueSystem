// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "UObject/Interface.h"
#include "ClueSystemUI_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClueSystemUI_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLUESYSTEM_API IClueSystemUI_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief Updates the Clue Viewer UI with the given Clue Data Asset
	 * @param Clue The Data Asset to update the UI with
	 * @return Whether or not the UI was updated successfully
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Clue System UI")
    bool UpdateClueViewer(const UPrimaryDataAsset_Clue* Clue);
};
