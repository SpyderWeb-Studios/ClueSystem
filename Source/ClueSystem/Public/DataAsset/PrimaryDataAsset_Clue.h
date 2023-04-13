// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/EClueLocation.h"
#include "Libraries/ClueStructLibrary.h"
#include "PrimaryDataAsset_Clue.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UPrimaryDataAsset_Clue : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPrimaryDataAsset_Clue();

#pragma region Getters

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetClueName(){return ClueName;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetClueInformation(){return ClueInformation;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetClueIndex() const {return ClueIndex;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetClueLocation() const {return ClueLocation;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FAdditionalClueInfo> GetAdditionalInformation(){return AdditionalInformation;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UStaticMesh* GetClueStaticMesh() const {return ClueMesh;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FRotator GetDefaultRotation() const {return DefaultRotation;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetCameraOffset() const {return CameraLocationOffset;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCameraDistance() const {return CameraDistance;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetDoesUseMesh() const{return bUsesMesh;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSoftObjectPtr<UTexture2D> GetClueImage() const {return ClueImage;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTexture2D* GetClueIcon() const {return ClueIcon;}

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
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category="Setup")
	int ClueIndex = -1;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Setup")
	FString ClueLocation;
		
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic|Setup")
	bool bUsesMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TObjectPtr<UTexture2D> ClueIcon;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	TArray<FAdditionalClueInfo> AdditionalInformation;
	
#pragma region Mesh
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information", meta=(EditCondition = "bUsesMesh == true", EditConditionHides))
	UStaticMesh* ClueMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information", meta=(EditCondition = "bUsesMesh == true", EditConditionHides))
	FRotator DefaultRotation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information", meta=(EditCondition = "bUsesMesh == true", EditConditionHides))
	FVector CameraLocationOffset;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information", meta=(EditCondition = "bUsesMesh == true", EditConditionHides))
	float CameraDistance;

#pragma endregion 

#pragma region Image
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information", meta=(EditCondition = "bUsesMesh == false", EditConditionHides))
	TObjectPtr<UTexture2D> ClueImage;
	
#pragma endregion

	
};
