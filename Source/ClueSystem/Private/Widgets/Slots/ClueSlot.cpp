// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Slots/ClueSlot.h"
#include "Engine/Texture2D.h"
#include "FunctionLibrary/MainDebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

void UClueSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_ViewClue->OnPressed.AddUniqueDynamic(this, &UClueSlot::ViewClue);

	if(UClueManagerSubsystem* ClueManagerSubsystem = GetGameInstance()->GetSubsystem<UClueManagerSubsystem>())
	{
		ClueManagerSubsystem->OnCollectedClue.AddUniqueDynamic(this, &UClueSlot::UpdateSlot);
	}
}

void UClueSlot::UpdateSlot(UPrimaryDataAsset_Clue* Clue)
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Updating Slot ["+FString::FromInt(GetNodeID()) +"]", EDebuggingType::DT_Log);
	
	if(!Clue || Clue->GetClueIndex() != GetNodeID()) return;
	
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data Asset With Index ["+ FString::FromInt(Clue->GetClueIndex()) +"] is Valid", EDebuggingType::DT_Log);

	TextBlock_ClueName->SetText(FText::FromString(Clue->GetClueName()));

	Image_ClueIcon->SetBrushFromSoftTexture(Clue->GetClueIcon());
	
	ClueData = Clue;
}

void UClueSlot::ViewClue()
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Attempting to View Clue [" +FString::FromInt(GetNodeID())+"]", EDebuggingType::DT_Log);

	// Async Load Data Asset
	if(ClueData.IsValid())
	{
		FStreamableManager StreamableManager;
		StreamableManager.RequestAsyncLoad(ClueData.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UClueSlot::OnDataLoaded));
	}
}

void UClueSlot::OnDataLoaded()
{
	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data is Loaded", EDebuggingType::DT_Log);
	if(ClueData.Get() && GetGameInstance()->GetSubsystem<UClueManagerSubsystem>()->HasCollectedClue(ClueData.Get()))
	{
		
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data is Valid", EDebuggingType::DT_Log);
		GetGameInstance()->GetSubsystem<UClueManagerSubsystem>()->OnClueSelected.Broadcast(ClueData.Get());
		
	}
}
