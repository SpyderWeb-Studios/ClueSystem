// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TamperComponent.h"

// Sets default values for this component's properties
UTamperComponent::UTamperComponent()
{
	SetIsReplicatedByDefault(true);
}

bool UTamperComponent::AttemptTamper_Implementation(TSubclassOf<UTamperObject> TamperClass, UObject* TamperTarget)
{
	if(IsValid(TamperTarget) && GetOwner()->HasAuthority() && TamperTarget->Implements<UTamperInterface>())
 	{
 		if(ITamperInterface::Execute_CanBeTamperedWithBy(TamperTarget, this) && ITamperInterface::Execute_IsTamperValid(TamperTarget, this))
 		{
 			return ITamperInterface::Execute_AttemptApplyTamper(TamperTarget, this);
 		}
 	}
 	
 	return false;
}


