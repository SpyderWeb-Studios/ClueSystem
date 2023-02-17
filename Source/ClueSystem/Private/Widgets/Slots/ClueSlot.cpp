// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Slots/ClueSlot.h"

#include "FunctionLibrary/MainDebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

void UClueSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_ViewClue->OnPressed.AddUniqueDynamic(this, &UClueSlot::ViewClue);

	OnDataAssetLoaded.AddUniqueDynamic(this, &UClueSlot::OnDataLoaded);
}

void UClueSlot::UpdateSlot(UPrimaryDataAsset_Clue* Clue)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Updating Slot", EDebuggingType::DT_Log);
	
	if(!Clue) return;
	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data Asset is Valid", EDebuggingType::DT_Log);

	TextBlock_ClueName->SetText(FText::FromString(Clue->GetClueName()));

	Image_ClueIcon->SetBrushFromSoftTexture(Clue->GetClueIcon());
	
	ClueData = Clue;
}

void UClueSlot::ViewClue()
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Attempting to View Clue", EDebuggingType::DT_Log);
	
	LoadData();
}

void UClueSlot::OnDataLoaded(UPrimaryDataAsset_Clue* Clue)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data is Loaded", EDebuggingType::DT_Log);
	if(Clue)
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data is Valid", EDebuggingType::DT_Log);
		GetGameInstance()->GetSubsystem<UClueManagerSubsystem>()->OnClueSelected.Broadcast(Clue);
		
	}
}
