// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"

#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "ZMBInteractableBase.generated.h"

UCLASS()
class SHOOTTHEMUP_API AZMBInteractableBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AZMBInteractableBase();



	virtual bool OnInteract_Implementation(AActor* Caller) override;
	virtual void StartFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;
};
