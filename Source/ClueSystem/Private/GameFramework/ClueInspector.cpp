// Fill out your copyright notice in the Description page of Project Settings.


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
	
	GetGameInstance()->GetSubsystem<UClueManagerSubsystem>()->OnClueSelected.AddUniqueDynamic(this, &AClueInspector::InspectClue);

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


	/* Display the Clue:
	 * Options:
	 *	- Load Mesh and Rotation from Data Asset:
	 *		- Can Change the Lighting and Rotation
	 *		- Quite heavy (though this is UE5 and is more than capable of doing it)
	 *		- Requires sending Mesh to a special location for rendering
	 *		
	 *	- Render an image of the Clue externally and import it in editor and load it here:
	 *		- No Dynamic Lighting
	 *		- More lightweight
	 *
	 *	- Let the Data Asset decide on which method it requires:
	 *		- Best of Both
	 *		- Could be potentially confusing to the player
	 *		- More Dynamic and scalable
	 */
	
	StaticMeshComponent->SetStaticMesh(ClueDataAsset->GetClueStaticMesh());

	// Log the Clue Mesh and Rotation
	UE_LOG(LogTemp, Warning, TEXT("Clue Mesh: %s"), *GetNameSafe(ClueDataAsset->GetClueStaticMesh()));
	UE_LOG(LogTemp, Warning, TEXT("Clue Rotation: %s"), *ClueDataAsset->GetDefaultRotation().ToString());
	
	StaticMeshComponent->SetWorldRotation(ClueDataAsset->GetDefaultRotation());

	FVector loc = ClueDataAsset->GetCameraOffset() + (CameraDefaultLocation * ClueDataAsset->GetCameraDistance());

	// Log the Clue Camera Location, with the Camera Offset and Camera Distance
	UE_LOG(LogTemp, Warning, TEXT("Clue Camera Relative Location: %s"), *loc.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Clue Camera Offset: %s"), *ClueDataAsset->GetCameraOffset().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Clue Camera Distance: %f"), ClueDataAsset->GetCameraDistance());	
	
	ClueCaptureComponent->SetRelativeLocation(loc);
}
