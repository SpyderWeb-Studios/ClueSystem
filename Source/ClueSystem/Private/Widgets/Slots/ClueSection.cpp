// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Slots/ClueSection.h"

#include "Components/PanelWidget.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"



void UClueSection::LoadBranch_Implementation()
{
	if(!SectionBranch.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Section Branch is not valid"));
		return;
	}
	// Load the Config Data Asset asynchonously
	FStreamableManager Streamable;
	Streamable.RequestAsyncLoad(SectionBranch.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UClueSection::OnSectionBranchLoaded));
}


void UClueSection::SetSectionSize(int SectionSize)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Setting Section Size to [" +FString::FromInt(SectionSize) +"]", EDebuggingType::DT_Log);
	
	SectionPanel->ClearChildren();
	SlotArray.Empty();

	for(int i =0 ; i< SectionSize; i++)
	{
		SlotArray.Add(CreateWidget<UClueSlot>(GetOwningPlayer(), ClueSlotClass));
		SectionPanel->AddChild(SlotArray[i]);
	}
}

void UClueSection::OnSectionBranchLoaded_Implementation()
{	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Section Branch Loaded", EDebuggingType::DT_Log);
	
	if(IsValid(SectionBranch.Get()))
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Section Branch: ["+ SectionBranch.Get()->GetClueLocation() +"] Valid", EDebuggingType::DT_Log);

		// If there are branches in the config, then we need to create a new section for each branch
		for(const auto& branch : SectionBranch.Get()->GetBranches())
		{
			// Continue if the branch is not valid
			if(!IsValid(branch))
			{
				UE_LOG(LogTemp, Warning, TEXT("Branch is not valid"));
				continue;
			}
			
			// Log the branch name
			UMainDebugFunctionLibrary::DebugLogWithObject(this, "Branch Name: [" +branch->GetClueLocation()+"]", EDebuggingType::DT_Log);
			
			// Create a new section for each branch
			UClueSection* section = CreateWidget<UClueSection>(GetOwningPlayer(), this->GetClass());
			section->SectionBranch = branch;
			section->LoadBranch();
			section->SetSectionSize(branch->GetClues().Num());
			SectionPanel->AddChild(section);
		}

		for(int i =0 ; i< SlotArray.Num(); i++)
		{
			UMainDebugFunctionLibrary::DebugLogWithObject(this, "Setting Slot ["+FString::FromInt(i)+"] Node ID to ["+FString::FromInt(SectionBranch.Get()->GetClues()[i]->GetClueIndex())+"]", EDebuggingType::DT_Log);
			SlotArray[i]->SetNodeID(SectionBranch.Get()->GetClues()[i]->GetClueIndex());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Section Branch is not valid"));
	}

}
