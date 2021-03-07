// Shoot Them Up Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUCoreTypes.h"
#include "STUFistWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUFistWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
protected:
	virtual void StartFire() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 1.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float DamageRadius = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float WeaponDamage = 10.0f;

	virtual void BeginPlay() override;
	virtual void MakeShot() override;
private:
	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	AController* GetController() const;
};
