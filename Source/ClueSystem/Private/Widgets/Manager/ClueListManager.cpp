// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Manager/ClueListManager.h"

#include "Components/PanelWidget.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

void UClueListManager::NativeConstruct()
{
	Super::NativeConstruct();
	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue List Manager Constructed", EDebuggingType::DT_Log);
	
	// Load the Config Data Asset asynchonously
	FStreamableManager Streamable;
	Streamable.RequestAsyncLoad(ClueConfig.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UClueListManager::OnConfigLoaded));
}



void UClueListManager::UpdateSectionTree(const FClueTree ClueTree)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Updating Section Tree", EDebuggingType::DT_Log);


	
	for(const auto& section : ClueTree.ClueTreeNodes[0].ChildrenNodes)
	{
		// Log the Clue Location and the Number of Clues
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Location: [" +section->GetClueLocation() +"] Number of Clues: ["+FString::FromInt(section->GetClues().Num())+"]", EDebuggingType::DT_Log); 
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
