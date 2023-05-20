// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/DataAsset.h"
#include "Libraries/ClueStructLibrary.h"
#include "PrimaryDataAsset_Clue.generated.h"

class UClueSection;
class UClueSlot;


/**
 * This is the base class for all clues. It contains only the information that is needed to display a clue in the UI. If you want to
 * create a new Clue Type, then extend this class and add your code in the new class. 
 */
UCLASS()
class CLUESYSTEM_API UPrimaryDataAsset_Clue : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPrimaryDataAsset_Clue();

	UFUNCTION(BlueprintCallable, Category="Clue System|Inspecting")
	virtual bool ViewClue(UWidgetSwitcher* ClueSwitcherSlot);

	UFUNCTION(BlueprintNativeEvent, Category="Clue System|Inspecting")
	bool StopViewingClue(UWidgetSwitcher* ClueSwitcherSlot);


	virtual bool IsSupportedForNetworking() const override;

#pragma region Getters

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	FString GetClueName(){return ClueName;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	FString GetClueInformation(){return ClueInformation;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	int GetClueIndex() const {return ClueIndex;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	FString GetClueLocation() const {return ClueLocation;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	TArray<FAdditionalClueInfo> GetAdditionalInformation(){return AdditionalInformation;}
	
	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	UTexture2D* GetClueIcon() const {return ClueIcon;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	TSubclassOf<UClueSlot> GetClueSlotClass() const {return ClueSlotClass;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	UStaticMesh* GetClueDisplayMesh() const {return ClueDisplayMesh;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	TSubclassOf<UUserWidget> GetClueWidgetClass() const {return ClueWidgetClass;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	UUserWidget* GetClueWidgetInstance() const {return ClueWidgetInstance;}

#pragma endregion 

#pragma region Setters
	
	void SetClueLocation(FString Location) {ClueLocation = Location;}

	void SetClueIndex(int Index) {ClueIndex = Index;}

#pragma endregion
	
protected:
	/**
	 * @brief The Name of the Clue to display in the UI
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic")
	FString ClueName;

	/**
	 * @brief The Information associated with the Clue 
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic")
    FString ClueInformation;

	/**
	 * @brief The Mesh that will be present in the World
	 */
	UPROPERTY(EditDefaultsOnly, Category="Basic")
	TObjectPtr<UStaticMesh> ClueDisplayMesh;

	/**
	 * @brief The Widget responsible for Inspecting the Clue
	 */
	UPROPERTY(EditDefaultsOnly, Category="Basic")
	TSubclassOf<UUserWidget> ClueWidgetClass;

	/**
	 * @brief The Index of the Clue. Will be filled in at Runtime
	 */
	 UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category="Setup")
	int ClueIndex = -1;

	/**
	 * @brief The Location of the Clue, will be filled in at Runtime
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Setup")
	FString ClueLocation;

	/**
	 * @brief The Icon to be displayed on the Clue Slot
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TObjectPtr<UTexture2D> ClueIcon;

	/**
	 * @brief The Widget Class that will be placed in the Branch Manager
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TSubclassOf<UClueSlot> ClueSlotClass;

	/**
	 * @brief The Information that is reliant on OTHER clues being collected
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TArray<FAdditionalClueInfo> AdditionalInformation;

private:
	/**
	 * @brief The Widget Instance that is created from the ClueWidgetClass
	 */
	 TObjectPtr<UUserWidget> ClueWidgetInstance;
};
