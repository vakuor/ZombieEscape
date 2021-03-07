// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Interactables/ZMBInteractiveActor.h"
#include "ZMBAmmoInteractiveActor.generated.h"

class ASTUBaseWeapon;
UCLASS()
class SHOOTTHEMUP_API AZMBAmmoInteractiveActor : public AZMBInteractiveActor
{
	GENERATED_BODY()

protected:
	virtual void OnUse_Implementation(const AActor* Caller) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	TSubclassOf<ASTUBaseWeapon> WeaponType;;

};
