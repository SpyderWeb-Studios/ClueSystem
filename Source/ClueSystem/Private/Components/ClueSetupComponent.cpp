// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "Components/ClueSetupComponent.h"

#include "Components/ClueManagerComponent.h"
#include "FunctionLibrary/DebugFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/ClueManagerSubsystem.h"
// Sets default values for this component's properties
UClueSetupComponent::UClueSetupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.


	// ...
}


// Called when the game starts
void UClueSetupComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->HasAuthority())
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Setup");

		// Get the Game Mode and find the Clue Manager Component
		if(const AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld()))
		{
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Game Mode Valid");
			if(UClueManagerComponent* manager = gameMode->FindComponentByClass<UClueManagerComponent>())
			{
				UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Valid");
				manager->SetClueConfigRoot(ClueConfig.Get());
			}
		}
	}
}

void UClueSetupComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(GetOwner()->HasAuthority())
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue End Play");

		// Get the Game Mode and find the Clue Manager Component
		if(const AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld()))
		{
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Game Mode Valid");
			if(UClueManagerComponent* manager = gameMode->FindComponentByClass<UClueManagerComponent>())
			{
				UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Valid");
				manager->Cleanup();
			}
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

