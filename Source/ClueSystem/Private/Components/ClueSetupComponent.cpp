// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "Components/ClueSetupComponent.h"

#include "FunctionLibrary/MainDebugFunctionLibrary.h"
#include "Enums/EDebuggingType.h"
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

	UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Setup", EDebuggingType::DT_Log);
	
	UClueManagerSubsystem* manager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UClueManagerSubsystem>();

	if(manager)
	{
		UMainDebugFunctionLibrary::DebugLogWithObject(this, "Clue Manager Valid", EDebuggingType::DT_Log);
		manager->SetClueConfigRoot(ClueConfig);
	}
}

