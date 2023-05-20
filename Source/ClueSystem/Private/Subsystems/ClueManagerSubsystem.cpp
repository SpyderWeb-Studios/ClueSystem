// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "Subsystems/ClueManagerSubsystem.h"

#include "ClueSystem.h"
#include "DataAsset/PrimaryDataAsset_ClueConfig.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"


UClueManagerSubsystem::UClueManagerSubsystem()
{
}

void UClueManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UClueManagerSubsystem::Deinitialize()
{
	Cleanup();
	
	Super::Deinitialize();
}

void UClueManagerSubsystem::Cleanup()
{
	OnClueSelected.Clear();
	OnCollectedClue.Clear();
}

void UClueManagerSubsystem::SelectClue(UPrimaryDataAsset_Clue* clue)
{
	UDebugFunctionLibrary::DebugLogWithObjectContext(this, "SelectClue called");
	if(IsValid(clue))
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue is valid, broadcasting OnClueSelected");
		OnClueSelected.Broadcast(clue);
	}
}

bool UClueManagerSubsystem::HasCollectedClue(UPrimaryDataAsset_Clue* ClueDataAsset)
{
	if(_playerClueManagerComponent.IsValid())
	{
		// Get ask the PlayerClueManagerComponent if it has collected the clue
		return _playerClueManagerComponent->HasCollectedClue(ClueDataAsset);
	}

	return false;
}

void UClueManagerSubsystem::SetPlayerClueManagerComponent(UPlayerClueManagerComponent* PlayerClueManagerComponent)
{
	this->_playerClueManagerComponent = PlayerClueManagerComponent;
}
