// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "ClueTypeMesh.generated.h"

/**
 * 
 */
UCLASS()
class CLUESYSTEM_API UClueTypeMesh : public UPrimaryDataAsset_Clue
{
	GENERATED_BODY()

protected:



#pragma region Mesh


	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	UStaticMesh* ClueMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	FRotator DefaultRotation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	FVector CameraLocationOffset;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	float CameraDistance;

#pragma endregion

public:
	
	UFUNCTION(BlueprintPure)
	UStaticMesh* GetClueStaticMesh() const {return ClueMesh;}

	UFUNCTION(BlueprintPure)
	FRotator GetDefaultRotation() const {return DefaultRotation;}

	UFUNCTION(BlueprintPure)
	FVector GetCameraOffset() const {return CameraLocationOffset;}

	UFUNCTION(BlueprintPure)
	float GetCameraDistance() const {return CameraDistance;}
	
};
