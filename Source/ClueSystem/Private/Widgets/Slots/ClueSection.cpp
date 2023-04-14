// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Slots/ClueSection.h"

#include "Components/PanelWidget.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"

void UClueSection::UpdateSection(UPrimaryDataAsset_Clue* ClueDataAsset)
{

	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Updating Section with Data Asset", EDebuggingType::DT_Log);

	if(!ClueDataAsset) return;
	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Data Asset is Valid: " +ClueDataAsset->GetClueName(), EDebuggingType::DT_Log);
	
	if(!Slots.Contains(ClueDataAsset->GetClueName()))
	{
		
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Slot TMap doesn't contain Clue", EDebuggingType::DT_Log);
		
		if(!SlotArray.IsValidIndex(ClueDataAsset->GetClueIndex()))
		{
			UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Index : "+ FString::FromInt(ClueDataAsset->GetClueIndex()) +" is Invalid", EDebuggingType::DT_Log);
			return;
		}
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Index is Valid", EDebuggingType::DT_Log);
		
		Slots.Add(ClueDataAsset->GetClueName(), SlotArray[ClueDataAsset->GetClueIndex()]);
		
	}

	Slots[ClueDataAsset->GetClueName()]->UpdateSlot(ClueDataAsset);
	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Updated Slot", EDebuggingType::DT_Log);
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
