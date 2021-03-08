// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Interactables/ZMBInteractiveActor.h"
#include "ZMBDoorInteractiveActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API AZMBDoorInteractiveActor : public AZMBInteractiveActor
{
	GENERATED_BODY()

protected:
	virtual void OnUse_Implementation(const AActor* Caller) override;

private:
	void Open();
};
