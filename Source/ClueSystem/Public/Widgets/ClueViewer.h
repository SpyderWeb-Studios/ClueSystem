// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "Slots/ClueDescriptionSlot.h"
#include "ClueViewer.generated.h"

/**
 * NOTE: This is a WIP Widget. This will need to be updated to handle the newer changes to the Clue System. Mainly,
 * the Clue Data Assets will tell this Widget how to display the Clue. For example, the Clue Data Asset will tell
 * this Widget whether to display the Clue as a 3D Mesh or as a 2D Image, or even as a audio file with a visualiser. 
 */
UCLASS()
class CLUESYSTEM_API UClueViewer : public UUserWidget
{
	GENERATED_BODY()

public:
	
virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClueSelected(UPrimaryDataAsset_Clue* CollectedClue);

	UFUNCTION(BlueprintCallable, Category="Clue System|Viewer")	
	void ResetViewer();
	
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget), Category="Clue System|Viewer")
	TObjectPtr<UWidgetSwitcher> ClueViewerSwitcher;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget), Category="Clue System|Viewer")
	TObjectPtr<UPanelWidget> ClueViewerPanel;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget), Category="Clue System|Viewer")
	UTextBlock* TextBlock_ClueDescription;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(BindWidget), Category="Clue System|Viewer")
	UVerticalBox* VerticalBox_ClueSections;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Clue System|Viewer")
	TSubclassOf<UClueDescriptionSlot> ClueDescriptionClass;

private:

	
	
};
