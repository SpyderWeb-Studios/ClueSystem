// Copyright 2022-2023 Spyderweb Studios Ltd. All Rights Reserved.


#include "GameFramework/ClueInspector.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Subsystems/ClueManagerSubsystem.h"

// Sets default values
AClueInspector::AClueInspector()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Clue Mesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	ClueCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("Clue Inspector");
	ClueCaptureComponent->SetupAttachment(StaticMeshComponent);
	ClueCaptureComponent->SetRelativeLocation(FVector(-1,0,0));
}

// Called when the game starts or when spawned
void AClueInspector::BeginPlay()
{
	Super::BeginPlay();
	
	CameraDefaultLocation = ClueCaptureComponent->GetRelativeLocation().GetSafeNormal();
}

void AClueInspector::InspectClue(UPrimaryDataAsset_Clue* ClueDataAsset)
{
	if(!IsValid(ClueDataAsset)) return;

	InspectClueMesh(Cast<UClueTypeMesh>(ClueDataAsset));
}

void AClueInspector::InspectClueMesh(UClueTypeMesh* ClueDataAsset)
{
	if(!IsValid(ClueDataAsset)) return;
		
	StaticMeshComponent->SetStaticMesh(ClueDataAsset->GetClueStaticMesh());

	// Log the Clue Mesh and Rotation
	// UE_LOG(LogTemp, Warning, TEXT("Clue Mesh: %s"), *GetNameSafe(ClueDataAsset->GetClueStaticMesh()));
	UE_LOG(LogTemp, Warning, TEXT("Clue Rotation: %s"), *ClueDataAsset->GetDefaultRotation().ToString());
	
	StaticMeshComponent->SetWorldRotation(ClueDataAsset->GetDefaultRotation());

	FVector loc = ClueDataAsset->GetCameraOffset() + (CameraDefaultLocation * ClueDataAsset->GetCameraDistance());

	// Log the Clue Camera Location, with the Camera Offset and Camera Distance
	UE_LOG(LogTemp, Warning, TEXT("Clue Camera Relative Location: %s"), *loc.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Clue Camera Offset: %s"), *ClueDataAsset->GetCameraOffset().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Clue Camera Distance: %f"), ClueDataAsset->GetCameraDistance());	
	
	ClueCaptureComponent->SetRelativeLocation(loc);
}
