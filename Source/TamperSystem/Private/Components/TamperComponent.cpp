// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TamperComponent.h"

// Sets default values for this component's properties
UTamperComponent::UTamperComponent()
{
	SetIsReplicatedByDefault(true);
}

bool UTamperComponent::AttemptTamper(UObject* Object)
{
	if(IsValid(Object) && GetOwner()->HasAuthority() && Object->Implements<UTamperInterface>())
	{
		if(ITamperInterface::Execute_CanBeTamperedWithBy(Object, this) && ITamperInterface::Execute_IsTamperValid(Object, this))
		{
			return ITamperInterface::Execute_AttemptApplyTamper(Object, this);
		}
	}
	
	return false;
}


