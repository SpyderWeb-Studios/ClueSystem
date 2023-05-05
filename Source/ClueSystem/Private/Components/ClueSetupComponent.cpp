// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "Components/ClueSetupComponent.h"

#include "FunctionLibrary/DebugFunctionLibrary.h"
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
	
		UClueManagerSubsystem* manager = GetWorld()->GetSubsystem<UClueManagerSubsystem>();

		if(manager && ClueConfig.IsValid())
		{
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Valid");
			manager->SetClueConfigRoot(ClueConfig.Get());
		}
	}
}

void UClueSetupComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(GetOwner()->HasAuthority())
	{
		UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Setup Ending Play");

		if(UClueManagerSubsystem* manager = GetWorld()->GetSubsystem<UClueManagerSubsystem>())
		{
			UDebugFunctionLibrary::DebugLogWithObjectContext(this, "Clue Manager Valid");
			manager->Cleanup();;
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

