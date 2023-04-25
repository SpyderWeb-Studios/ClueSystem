// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PrimaryDataAsset_Clue.h"
#include "ClueTypeMesh.generated.h"

/**
 * This is a Clue Type that contains a mesh, it extends the Clue Data Asset and displays a mesh in the Clue Widget. It holds information
 * on how to display the mesh in the widget, which includes the transformation of the mesh, the camera distance (how far away the mesh should be by default)
 * and even the name of the Inspector that should be used to display the mesh in the widget. This is to enable different inspectors to be used for different
 * meshes and areas for streaming purposes.
 */
UCLASS()
class CLUESYSTEM_API UClueTypeMesh : public UPrimaryDataAsset_Clue
{
	GENERATED_BODY()

protected:

#pragma region Mesh

	/**
	 * @brief The mesh that should be displayed in the Clue Widget. Different from the Display Mesh as this should be the high resolution one
	 * as it will be viewed in the Clue Widget
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	UStaticMesh* ClueMesh;

	/**
	 * @brief The Default rotation that the mesh should be displayed at in the Clue Widget
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	FRotator DefaultRotation;

	/**
	 * @brief The Offset from the Camera that the mesh should be displayed at in the Clue Widget
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	FVector CameraLocationOffset;

	/**
	 * @brief The default distance that the camera should be from the mesh in the Clue Widget
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Information")
	float CameraDistance;

	/**
	 * @brief The Identification of the Inspector that should be used to display the mesh in the Clue Widget.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Setup")
	FString MeshInspectorName = "";

#pragma endregion

public:
	
	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	UStaticMesh* GetClueStaticMesh() const {return ClueMesh;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	FRotator GetDefaultRotation() const {return DefaultRotation;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	FVector GetCameraOffset() const {return CameraLocationOffset;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	float GetCameraDistance() const {return CameraDistance;}

	UFUNCTION(BlueprintPure, Category="Clue System|Information")
	FString GetMeshInspectorName() const {return MeshInspectorName;}
	
};
