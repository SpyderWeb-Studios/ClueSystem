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
	
	FString GetClueName(){return ClueName;}

	FString GetClueInformation(){return ClueInformation;}
	
	int GetClueIndex() const {return ClueIndex;}

	EClueLocation GetClueLocation() const {return ClueLocation;}

	TArray<FAdditionalClueInfo> GetAdditionalInformation(){return AdditionalInformation;}

	UStaticMesh* GetClueStaticMesh() const {return ClueMesh;}

	FRotator GetDefaultRotation() const {return DefaultRotation;}

	FVector GetCameraOffset() const {return CameraLocationOffset;}
	
	float GetCameraDistance() const {return CameraDistance;}

	bool GetDoesUseMesh() const{return bUsesMesh;}

	TSoftObjectPtr<UTexture2D> GetClueImage() const {return ClueImage;}
	
	TObjectPtr<UTexture2D> GetClueIcon() const {return ClueIcon;}

#pragma endregion 

#pragma region Setters
	
	void SetClueLocation(EClueLocation Location) {ClueLocation = Location;}

	void SetClueIndex(int Index) {ClueIndex = Index;}

#pragma endregion
	
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic")
	FString ClueName;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Basic")
    FString ClueInformation;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Setup")
	int ClueIndex;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Setup")
	TEnumAsByte<EClueLocation> ClueLocation;
		
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
