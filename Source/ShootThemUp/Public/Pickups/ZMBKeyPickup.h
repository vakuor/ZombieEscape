// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "ZMBKeyPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API AZMBKeyPickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	int Count = 1;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
