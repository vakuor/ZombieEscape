// Zombie Escape Game. All rights reserved!

#include "Interfaces/ZMBInteractableBase.h"

AZMBInteractableBase::AZMBInteractableBase()
{
 	PrimaryActorTick.bCanEverTick = false;
}

bool AZMBInteractableBase::OnInteract_Implementation(AActor* Caller)
{
	return false;
}

void AZMBInteractableBase::StartFocus_Implementation()
{
}

void AZMBInteractableBase::EndFocus_Implementation()
{
}

