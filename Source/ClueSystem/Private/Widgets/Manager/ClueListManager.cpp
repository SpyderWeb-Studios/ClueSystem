// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Manager/ClueListManager.h"

#include "Components/PanelWidget.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

void UClueListManager::NativeConstruct()
{
	Super::NativeConstruct();


	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue List Manager Constructed", EDebuggingType::DT_Log);
	
	if(UClueManagerSubsystem* manager = GetGameInstance()->GetSubsystem<UClueManagerSubsystem>())
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Manager Subsystem Valid", EDebuggingType::DT_Log);

		manager->OnCollectedClue.AddUniqueDynamic(this, &UClueListManager::UpdateSlotList);
		manager->OnUpdateClueSectionSize.AddUniqueDynamic(this, &UClueListManager::UpdateSectionSize);

		manager->BroadcastNumberOfClues();
	}
	
}

void UClueListManager::UpdateSlotList(UPrimaryDataAsset_Clue* CollectedClue)
{
	if(!CollectedClue) return;
	UClueSection* ClueSection;
	// If the Section is in the Map, then update the value
	if(CollectedClueSections.Contains(CollectedClue->GetClueLocation()))
	{
		ClueSection = CollectedClueSections[CollectedClue->GetClueLocation()];
	}
	// If it isn't in the Map, create a Section
	else
	{
		ClueSection = CreateWidget<UClueSection>(GetOwningPlayer(), ClueSectionClass);
		CollectedClueSections.Add(CollectedClue->GetClueLocation(), ClueSection);
	}

	ClueSection->UpdateSection(CollectedClue);
}

void UClueListManager::UpdateSectionSize(EClueLocation ClueLocation, int SectionSize)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Section Size: " +FString::FromInt(SectionSize), EDebuggingType::DT_Log);
	UClueSection* section;
	if(!CollectedClueSections.Contains(ClueLocation))
	{
		section = CreateWidget<UClueSection>(GetOwningPlayer(), ClueSectionClass);
		GetParent()->AddChild(section);
		CollectedClueSections.Add(ClueLocation, section);
	}
	else
	{
		section = CollectedClueSections[ClueLocation];
	}
	if(section) section->SetSectionSize(SectionSize);
}


