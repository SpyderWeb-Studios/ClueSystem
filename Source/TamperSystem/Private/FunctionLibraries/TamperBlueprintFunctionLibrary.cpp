// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/TamperBlueprintFunctionLibrary.h"

UTamperObject* UTamperBlueprintFunctionLibrary::AddTamper(TSubclassOf<UTamperObject> TamperClass, UObject* TargetObject,
	bool bAutoActivate)
{
	if(!IsValid(TargetObject))
	{
		return nullptr;
	}

	if(!IsValid(TamperClass))
	{
		return nullptr;
	}

	// only the server can create new spells.
	if(TargetObject->GetWorld()->GetNetMode() >= NM_Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("Only the server can create new Tamper Objects."));
		return nullptr;
	}

	checkf(TargetObject->GetClass()->ImplementsInterface(UTamperInterface::StaticClass()),
		TEXT("TargetObject must implement the TamperInterface."));

	checkf(TamperClass->IsChildOf(UTamperObject::StaticClass()),
		TEXT("TamperClass must be a child of UTamperObject."));
	
	return NewObject<UTamperObject>(TargetObject, TamperClass);
}

UTamperObject* UTamperBlueprintFunctionLibrary::RegisterTamperObject(UObject* Target,UTamperObject* TamperObject)
{
	if(!IsValid(TamperObject))
	{
		return nullptr;
	}

	if(!IsValid(Target))
	{
		return nullptr;
	}

	// Register the spell
	if(!ITamperInterface::Execute_RegisterTamperObject(Target, TamperObject))
	{
		TamperObject->BeginDestroy();
		TamperObject = nullptr;
		return nullptr;
	}
	
	return TamperObject;
}

void UTamperBlueprintFunctionLibrary::DestroyTamperObject(UTamperObject* TamperObject)
{
}
