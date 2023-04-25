// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "Widgets/Manager/ClueBranchManager.h"

#include "Components/PanelWidget.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
#include "Engine/StreamableManager.h"
#include "Widgets/Slots/ClueSlot.h"

void UClueBranchManager::OnClueConfigLoaded_Implementation() const
{
	// Log that the Clue Config was loaded.
	UE_LOG(LogTemp, Warning, TEXT("Clue Config Loaded"));

	// Get the Clue Config from the Soft Object Pointer and validate it.
	UPrimaryDataAsset_ClueConfig* ClueConfigAsset = ClueConfig.Get();
	if (ClueConfigAsset)
	{
		// Log the Clue Config's Clue Location.
		UE_LOG(LogTemp, Warning, TEXT("Clue Config Clue Location: %s"), *ClueConfigAsset->GetClueLocation());

		// Log the Clue Config's Clue Branch Manager Class.
		UE_LOG(LogTemp, Warning, TEXT("Clue Config Clue Branch Manager Class: %s"), *ClueConfigAsset->GetClueBranchManagerClass()->GetName());

		// Log the Clue Config's Clue Branches.
		UE_LOG(LogTemp, Warning, TEXT("Clue Config Num Clue Branches: %d"), ClueConfigAsset->GetBranches().Num());

		// Log the Clue Config's Clues.
		UE_LOG(LogTemp, Warning, TEXT("Clue Config Num Clues: %d"), ClueConfigAsset->GetClues().Num());

		// Create a Clue Slot Widget for each Clue.
		for (const UPrimaryDataAsset_Clue* Clue : ClueConfigAsset->GetClues())
		{
			
			if(!IsValid(Clue) || !IsValid(Clue->GetClueSlotClass()))
			{
				UE_LOG(LogTemp, Error, TEXT("Clue or Clue Slot Class is invalid"));
				continue;
			}
						
			
			// Create the Clue Slot Widget.
			UClueSlot* ClueSlot = CreateWidget<UClueSlot>(GetWorld(), Clue->GetClueSlotClass());

			ClueSlot->ClueData = Clue;
			ClueSlot->SetNodeID(Clue->GetClueIndex());

			// Add the Clue Slot Widget to the Clue Branch Manager Widget's Clues Box.
			ClueBranchesPanel->AddChild(ClueSlot);
			
		}
		
		// Create a Clue Branch Manager Widget for each Clue Branch.
		for (const UPrimaryDataAsset_ClueConfig* ClueBranch : ClueConfigAsset->GetBranches())
		{
			// Validate the Clue Branch.
			if (!IsValid(ClueBranch))
			{
				UE_LOG(LogTemp, Error, TEXT("Clue Branch is invalid"));
				continue;
			}
			// Validate the Clue Branch's Clue Branch Manager Class.
			if (!IsValid(ClueBranch->GetClueBranchManagerClass()))
			{
				UE_LOG(LogTemp, Error, TEXT("Clue Branch Manager Class is invalid"));
				continue;
			}
			
			
			// Create the Clue Branch Manager Widget.
			UClueBranchManager* ClueBranchManager = CreateWidget<UClueBranchManager>(GetWorld(), ClueBranch->GetClueBranchManagerClass());

			// Set the Clue Branch Manager Widget's Clue Config.
			ClueBranchManager->SetClueConfig(ClueBranch);

			// Add the Clue Branch Manager Widget to the Clue Branch Manager Widget's Clue Branches Box.
			ClueBranchesPanel->AddChild(ClueBranchManager);
		}
		
	}
	else
	{
		// Log that the Clue Config was not loaded.
		UE_LOG(LogTemp, Warning, TEXT("Clue Config Not Loaded"));
	}
}


void UClueBranchManager::NativeConstruct()
{
	Super::NativeConstruct();

	// Log that this widget was constructed.
	UE_LOG(LogTemp, Warning, TEXT("Clue Branch Manager Constructed"));

	// Load the Clue Config from the Soft Object Pointer asynchronosly.
	FStreamableManager Streamable;
	Streamable.RequestAsyncLoad(ClueConfig.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UClueBranchManager::OnClueConfigLoaded));
}
