// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "DataAsset/ClueTypes/ClueTypeMesh.h"
#include "GameFramework/Actor.h"
#include "ClueInspector.generated.h"

/*
 * This Actor is used to inspect Clues in the world. It has to be placed in the world and then have it's
 * Identifier set. This Identifier is used to identify which Clue Inspector is being used.
 */
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
	UPROPERTY(Category = "Clue System|Inspector", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	/**
	 * @brief The Scene Capture Component that will render the Clue for Inspection
	 */
	UPROPERTY(Category = "Clue System|Inspector", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneCaptureComponent2D>  ClueCaptureComponent;

	/**
	 * @brief A Getter for the Inspector Identifier
	 * @return The Inspector Identifier String
	 */
	UFUNCTION(BlueprintPure, Category = "Clue System|Inspector")
		FORCEINLINE FString GetInspectorIdentifier() const { return InspectorIdentifier; }

	/**
	 * @brief Sets up the Inspector to render the Clue Data Asset passed in
	 * @param ClueDataAsset The Data Asset to Render. Will fail if the Data Asset is not a Mesh Type
	 */
	UFUNCTION(BlueprintCosmetic, BlueprintCallable, Category = "Clue System|Inspector")
		void InspectClue(UPrimaryDataAsset_Clue* ClueDataAsset);

	/**
	 * @brief More specific version of InspectClue that takes a ClueTypeMesh Data Asset, this
	 * will render the Mesh type Clue Data Asset
	 * @param ClueDataAsset The Data Asset to Render
	 */
	UFUNCTION(BlueprintCosmetic, BlueprintCallable, Category = "Clue System|Inspector")
    	void InspectClueMesh(UClueTypeMesh* ClueDataAsset);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Clue System|Inspector")
		FString InspectorIdentifier;

private:

	FVector CameraDefaultLocation;

};
