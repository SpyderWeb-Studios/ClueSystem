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
	}
	
	// Load the Config Data Asset asynchonously
	FStreamableManager Streamable;
	Streamable.RequestAsyncLoad(ClueConfig.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UClueListManager::OnConfigLoaded));
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

void UClueListManager::UpdateSectionSize(const FString& ClueLocation, int SectionSize)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Section Size: " +FString::FromInt(SectionSize), EDebuggingType::DT_Log);
	UClueSection* section;

	if(SectionSize <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Section Size for location [%s] is less than or equal to 0"), *ClueLocation);
		return;
	}
	
	if(!CollectedClueSections.Contains(ClueLocation))
	{
		section = CreateWidget<UClueSection>(GetOwningPlayer(), ClueSectionClass);
		CollectedClueSections.Add(ClueLocation, section);
	}
	else
	{
		section = CollectedClueSections[ClueLocation];
	}
	if(section) section->SetSectionSize(SectionSize);
}

void UClueListManager::UpdateSectionTree(const FClueTree ClueTree)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Updating Section Tree", EDebuggingType::DT_Log);
	for(const auto& section : ClueTree.ClueTreeNodes)
	{
		UpdateSectionSize(section.Value.NodeName, section.Value.Clues.Num());
	}

	// Iterate through the Collected Clue Sections
	for(const auto& section : CollectedClueSections)
	{
		if(IsValid(section.Value))
		{
			UMainDebugFunctionLibrary::DebugLogWithObject(this, "Section Value [" +section.Key +"] Valid. Number of Clues ["+
				FString::FromInt(section.Value->GetSectionSize()) +"]", EDebuggingType::DT_Log);
			GetParent()->AddChild(section.Value);
		}
	}
}

void UClueListManager::OnConfigLoaded()
{
	// Get the Config Data Asset
	if(UPrimaryDataAsset_ClueConfig* config = ClueConfig.Get())
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Config Data Asset Valid", EDebuggingType::DT_Log);

		LocalClueTree.Empty();
		GetGameInstance()->GetSubsystem<UClueManagerSubsystem>()->CreateTreeRecursively(ClueConfig.Get(), LocalClueTree);
		
		UpdateSectionTree(LocalClueTree);
	}
}
