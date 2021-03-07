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
public:
	ASTUFistWeapon();
	virtual void StartFire() override;
	virtual void StopFire() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 1.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float WeaponDamage = 10.0f;

	UPROPERTY(VisibleAnywhere, Category="VFX")
	USTUWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* TraceFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FString TraceTargetName = "TraceTarget";

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
private:
	FTimerHandle ShotTimerHandle;
	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	void MakeDamage(const FHitResult& HitResult);
	void InitFX();
	void SetMuzzleFXActive(bool IsActive);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	AController* GetController() const;
};
