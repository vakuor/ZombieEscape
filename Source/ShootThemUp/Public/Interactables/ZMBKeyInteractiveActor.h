// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Interactables/ZMBInteractiveActor.h"
#include "ZMBKeyInteractiveActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API AZMBKeyInteractiveActor : public AZMBInteractiveActor
{
	GENERATED_BODY()

protected:
	virtual void OnUse_Implementation(const AActor* Caller) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	int Count = 1;
};
