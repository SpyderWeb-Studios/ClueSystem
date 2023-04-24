// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/PrimaryDataAsset_Clue.h"

#include "Components/PanelWidget.h"

UPrimaryDataAsset_Clue::UPrimaryDataAsset_Clue()
{
}

bool UPrimaryDataAsset_Clue::StopViewingClue_Implementation(UPanelWidget* ClueSwitcherSlot)
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

bool UPrimaryDataAsset_Clue::ViewClue(UPanelWidget* ClueSwitcherSlot)
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

	ClueWidgetInstance = CreateWidget<UUserWidget>(ClueSwitcherSlot->GetOwningPlayer(), GetClueWidgetClass());
	
	ClueSwitcherSlot->AddChild(ClueWidgetInstance);
	
	return true;
}
