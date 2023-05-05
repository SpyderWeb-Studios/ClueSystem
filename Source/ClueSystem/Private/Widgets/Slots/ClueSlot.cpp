// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "Widgets/Slots/ClueSlot.h"
#include "Engine/Texture2D.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "Subsystems/ClueManagerSubsystem.h"

void UClueSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_ViewClue->OnPressed.AddUniqueDynamic(this, &UClueSlot::ViewClue);

	if(UClueManagerSubsystem* ClueManagerSubsystem =GetWorld()->GetSubsystem<UClueManagerSubsystem>())
	{
		ClueManagerSubsystem->OnCollectedClue.AddUniqueDynamic(this, &UClueSlot::UpdateSlot);
	}
}

void UClueSlot::UpdateSlot(UPrimaryDataAsset_Clue* Clue)
{
	UDebugFunctionLibrary::DebugLogWithObject(this, "Updating Slot ["+FString::FromInt(GetNodeID()) +"]");
	
	if(!Clue || Clue->GetClueIndex() != GetNodeID()) return;
	
	UDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data Asset With Index ["+ FString::FromInt(Clue->GetClueIndex()) +"] is Valid");

	TextBlock_ClueName->SetText(FText::FromString(Clue->GetClueName()));

	Image_ClueIcon->SetBrushFromSoftTexture(Clue->GetClueIcon());
	
	ClueData = Clue;
}

void UClueSlot::ViewClue()
{
	UDebugFunctionLibrary::DebugLogWithObject(this, "Attempting to View Clue [" +FString::FromInt(GetNodeID())+"]");

	// Async Load Data Asset
	if(ClueData.IsValid())
	{
		FStreamableManager StreamableManager;
		StreamableManager.RequestAsyncLoad(ClueData.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UClueSlot::OnDataLoaded));
	}
}

void UClueSlot::OnDataLoaded()
{
	UDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data is Loaded");
	if(ClueData.Get() && GetWorld()->GetSubsystem<UClueManagerSubsystem>()->HasCollectedClue(ClueData.Get()))
	{
		
		UDebugFunctionLibrary::DebugLogWithObject(this, "Clue Data is Valid");
		GetWorld()->GetSubsystem<UClueManagerSubsystem>()->OnClueSelected.Broadcast(ClueData.Get());
		
	}
}
