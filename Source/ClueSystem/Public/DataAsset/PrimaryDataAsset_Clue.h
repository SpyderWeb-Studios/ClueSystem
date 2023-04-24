// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelSlot.h"
#include "Engine/DataAsset.h"
#include "Libraries/ClueStructLibrary.h"
#include "PrimaryDataAsset_Clue.generated.h"

class UClueSection;
class UClueSlot;


/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UPrimaryDataAsset_Clue : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPrimaryDataAsset_Clue();

	UFUNCTION(BlueprintCallable)
	virtual bool ViewClue(UPanelWidget* ClueSwitcherSlot);

	UFUNCTION(BlueprintNativeEvent)
	bool StopViewingClue(UPanelWidget* ClueSwitcherSlot);

#pragma region Getters

	UFUNCTION(BlueprintPure)
	FString GetClueName(){return ClueName;}

	UFUNCTION(BlueprintPure)
	FString GetClueInformation(){return ClueInformation;}

	UFUNCTION(BlueprintPure)
	int GetClueIndex() const {return ClueIndex;}

	UFUNCTION(BlueprintPure)
	FString GetClueLocation() const {return ClueLocation;}

	UFUNCTION(BlueprintPure)
	TArray<FAdditionalClueInfo> GetAdditionalInformation(){return AdditionalInformation;}
	
	UFUNCTION(BlueprintPure)
	UTexture2D* GetClueIcon() const {return ClueIcon;}

	UFUNCTION(BlueprintPure)
	TSubclassOf<UClueSlot> GetClueSlotClass() const {return ClueSlotClass;}

	UFUNCTION(BlueprintPure)
	UStaticMesh* GetClueDisplayMesh() const {return ClueDisplayMesh;}

	UFUNCTION(BlueprintPure)
	TSubclassOf<UUserWidget> GetClueWidgetClass() const {return ClueWidgetClass;}

	UFUNCTION(BlueprintPure)
	UUserWidget* GetClueWidgetInstance() const {return ClueWidgetInstance;}

#pragma endregion 

#pragma region Setters
	
	void SetClueLocation(FString Location) {ClueLocation = Location;}

	void SetClueIndex(int Index) {ClueIndex = Index;}

#pragma endregion
	
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic")
	FString ClueName;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic")
    FString ClueInformation;

	UPROPERTY(EditDefaultsOnly, Category="Basic")
	TObjectPtr<UStaticMesh> ClueDisplayMesh;

	UPROPERTY(EditDefaultsOnly, Category="Basic")
	TSubclassOf<UUserWidget> ClueWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category="Setup")
	int ClueIndex = -1;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Setup")
	FString ClueLocation;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TObjectPtr<UTexture2D> ClueIcon;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TSubclassOf<UClueSlot> ClueSlotClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TArray<FAdditionalClueInfo> AdditionalInformation;

private:
	
	TObjectPtr<UUserWidget> ClueWidgetInstance;
};
