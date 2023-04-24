// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "DataAsset/ClueTypes/ClueTypeMesh.h"
#include "GameFramework/Actor.h"
#include "ClueInspector.generated.h"

UCLASS()
class CLUESYSTEM_API AClueInspector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClueInspector();
	
	/**
	 * @brief The mesh that will update when a Clue is Selected for Inspection
	 */
	UPROPERTY(Category = "Stamina|Main", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(Category = "Stamina|Main", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneCaptureComponent2D>  ClueCaptureComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void InspectClue(UPrimaryDataAsset_Clue* ClueDataAsset);

	UFUNCTION(BlueprintCallable)
		void InspectClueMesh(UClueTypeMesh* ClueDataAsset);

private:

	FVector CameraDefaultLocation;

};
