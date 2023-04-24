// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ClueViewer.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

void UClueViewer::NativeConstruct()
{
	Super::NativeConstruct();

	if(UClueManagerSubsystem* ClueManagerSubsystem = GetGameInstance()->GetSubsystem<UClueManagerSubsystem>())
	{
		ClueManagerSubsystem->OnClueSelected.AddUniqueDynamic(this, &UClueViewer::OnClueSelected);
	}
}

void UClueViewer::OnClueSelected(UPrimaryDataAsset_Clue* CollectedClue)
{
	if(!CollectedClue) return;
	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Received Clue to View: " +CollectedClue->GetClueName(), EDebuggingType::DT_Both);

	/* Display the Description and what it means from Data Asset
	 * - Base Description
	 * - Additional Description dependent on other clues:
	 *    - Check if Clue Name is in the Clue Manager
	 *    - If so then load in the additional information
	 */

	// View the Collected Clue
	//CollectedClue->ViewClue(ClueViewerPanel->GetSlots()[0]);

	if(!IsValid(ClueViewerPanel))
	{
		// Log to say that the Clue Viewer Panel is Invalid
		UE_LOG(LogBlueprint, Error, TEXT("Clue Viewer Panel is Invalid"));
		return;
	}


	if(!CollectedClue->ViewClue(ClueViewerPanel))
	{
		// Log to say that the Clue could not be viewed
		UE_LOG(LogBlueprint, Error, TEXT("Clue could not be viewed"));
	}
	
	// Simply Set the Clue Description from the Clue Information
	TextBlock_ClueDescription->SetText(FText::FromString(CollectedClue->GetClueInformation()));

	// Get rid of the previously selected Clue's Additional Information
	VerticalBox_ClueSections->ClearChildren();
	
	// Check if the Clue has any Additional Information
	if(CollectedClue->GetAdditionalInformation().Num() > 0)
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue has additional information: " +CollectedClue->GetClueName(), EDebuggingType::DT_Both);

		// Get the Clue Manager Subsystem
		if(UClueManagerSubsystem* ClueManagerSubsystem = GetGameInstance()->GetSubsystem<UClueManagerSubsystem>())
		{
			// For every piece of Additional Information, check if the reliant Clue has been collected
			for(auto Information : CollectedClue->GetAdditionalInformation())
			{
				// If the Clue Data Asset isn't Valid, move onto the next one
				if(!Information.ClueDataAsset) continue;

				// Check to see if the Clue Manager has registered the Player as having Collected the Clue
				const bool result = ClueManagerSubsystem->HasCollectedClue(Information.ClueDataAsset);
				
				UMainDebugFunctionLibrary::DebugLogWithObject(this, Information.ClueDataAsset->GetClueName() + " Reveals: "
					+ (result ? Information.Information : " Not In Clue Manager"), 
					EDebuggingType::DT_Both);

				// Create a Description Slot
				// It is defaulted to "???" to convey to the player that there is more information to gather based on another Clue
				UClueDescriptionSlot* slot = CreateWidget<UClueDescriptionSlot>(GetOwningPlayer(), ClueDescriptionClass);

				// If the Clue is Collected, Update the Slot to contain the new Information
				if(result) slot->UpdateClueDescription(Information.Information);

				// Add the Child to the ScrollBox
				VerticalBox_ClueSections->AddChild(slot);
			}
		}
	}
}

void UClueViewer::ResetViewer()
{
	VerticalBox_ClueSections->ClearChildren();
	TextBlock_ClueDescription->SetText(FText());
}
