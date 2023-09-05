// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PlayerClueManagerComponent.h"
#include "Libraries/ClueStructLibrary.h"
#include "Libraries/EventDelegateLibrary.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ClueManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueManagerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	UClueManagerSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void Cleanup();

	UFUNCTION(BlueprintCosmetic, BlueprintCallable, Category="Clue System|Clue Manager")
	void SelectClue(UPrimaryDataAsset_Clue* clue);
	
	bool HasCollectedClue(UPrimaryDataAsset_Clue* ClueDataAsset);

#pragma region Events
	
	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnCollectedClue OnCollectedClue;
	
	UPROPERTY(BlueprintAssignable, Category="Clue System|Clue Manager|Events")
	FOnClueSelected OnClueSelected;

#pragma endregion

	void SetPlayerClueManagerComponent(UPlayerClueManagerComponent* PlayerClueManagerComponent);

private:
	
	TWeakObjectPtr<UPlayerClueManagerComponent> _playerClueManagerComponent;

};
