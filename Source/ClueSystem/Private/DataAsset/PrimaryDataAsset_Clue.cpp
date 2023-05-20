// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "DataAsset/PrimaryDataAsset_Clue.h"

#include "Components/PanelWidget.h"
#include "Interfaces/ClueSystemUI_Interface.h"

UPrimaryDataAsset_Clue::UPrimaryDataAsset_Clue()
{
}

bool UPrimaryDataAsset_Clue::StopViewingClue_Implementation(UWidgetSwitcher* ClueSwitcherSlot)
{
	// Log a warning that this function has not been implemented.
	UE_LOG(LogTemp, Warning, TEXT("StopViewingClue has been implemented for %s"), *GetNameSafe(this));

	if(!IsValid(ClueSwitcherSlot))
	{
		// Log an Error that the ClueSwitcherSlot is not valid.
		UE_LOG(LogTemp, Error, TEXT("ClueSwitcherSlot is not valid for %s"), *GetNameSafe(this));
		return false;
	}

	if(!IsValid(ClueWidgetInstance))
	{
		// Log an Error that the ClueWidgetInstance is not valid.
		UE_LOG(LogTemp, Error, TEXT("ClueWidgetInstance is not valid for %s"), *GetNameSafe(this));
		return false;
	}

	ClueSwitcherSlot->RemoveChild(ClueWidgetInstance);
	
	return true;
}

bool UPrimaryDataAsset_Clue::ViewClue(UWidgetSwitcher* ClueSwitcherSlot)
{
	// Log a warning that this function has not been implemented.
	UE_LOG(LogTemp, Warning, TEXT("ViewClue has been implemented for %s"), *GetNameSafe(this));

	if(!IsValid(GetClueWidgetClass()))
	{
		// Log an Error that the ClueWidgetClass is not valid.
		UE_LOG(LogTemp, Error, TEXT("ClueWidgetClass is not valid for %s"), *GetNameSafe(this));
		return false;
	}

	// Validate the Panel Widget
	if(!IsValid(ClueSwitcherSlot))
	{
		// Log an Error that the ClueSwitcherSlot is not valid.
		UE_LOG(LogTemp, Error, TEXT("ClueSwitcherSlot is not valid for %s"), *GetNameSafe(this));
		return false;
	}

	// Look for an instance of the widget class in the widget switcher
	int index = -1;
	for(int i = 0; i < ClueSwitcherSlot->GetAllChildren().Num(); i++)
	{
		if(ClueSwitcherSlot->GetAllChildren()[i]->GetClass() == GetClueWidgetClass())
		{
			index = i;
			break;
		}
	}

	UWidget* active;
	
	// If the widget already exists, then update it to use the new data
	if(index >= 0)
	{
		// Log a warning that the widget already exists.
		UE_LOG(LogTemp, Warning, TEXT("ClueWidgetInstance already exists for %s"), *GetNameSafe(this));

		active = ClueSwitcherSlot->GetAllChildren()[index];
		
	}
	// Otherwise, create an instance of the widget and add it to the switcher
	else
	{
		// Log a warning that the widget doesn't exist.
		UE_LOG(LogTemp, Warning, TEXT("ClueWidgetInstance of Class [%s] doesn't exist for %s"),*GetNameSafe(GetClueWidgetClass()), *GetNameSafe(this));

		// Create an instance of the widget
		ClueWidgetInstance = CreateWidget<UUserWidget>(ClueSwitcherSlot->GetOwningPlayer(), GetClueWidgetClass());

		// Add the widget to the switcher
		ClueSwitcherSlot->AddChild(ClueWidgetInstance);

		active = ClueWidgetInstance;
	}

	if(IsValid(active))
	{
		// Log to say that the active widget has been set.
		UE_LOG(LogTemp, Warning, TEXT("Active widget has been set for %s"), *GetNameSafe(this));

		IClueSystemUI_Interface::Execute_UpdateClueViewer(active, this);
		
		// Set the active widget to the one matching the class
		ClueSwitcherSlot->SetActiveWidget(active);
		return true;
	}
	
	return false;
}

bool UPrimaryDataAsset_Clue::IsSupportedForNetworking() const
{
	return true;
}
