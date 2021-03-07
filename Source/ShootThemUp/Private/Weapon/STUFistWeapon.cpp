// Shoot Them Up Game. All rights reserved!


#include "Weapon/STUFistWeapon.h"
#include "NiagaraComponent.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Animations/AnimUtils.h"
#include "AI/STUAICharacter.h"
DEFINE_LOG_CATEGORY_STATIC(LogFistWeapon, All, All)

ASTUFistWeapon::ASTUFistWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUFistWeapon::StartFire()
{
	UE_LOG(LogFistWeapon, Display, TEXT("Vistrel kylaka"));
	InitFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTUFistWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASTUFistWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXActive(false);
}

bool ASTUFistWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASTUFistWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASTUFistWeapon::MakeShot()
{
	if(!GetWorld())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)){
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;
	if(HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

		//if( HitResult.Actor.IsValid() && HitResult.Actor->IsA())
		MakeDamage(HitResult);
		
		WeaponFXComponent->PlayImpactFX(HitResult);
		UE_LOG(LogFistWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
	} else
	{
	DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
}

void ASTUFistWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto Target = HitResult.GetActor();
	if(!Target) return;
	
	Target->TakeDamage(WeaponDamage, FDamageEvent(), GetController(), this);
	auto Character = Cast<ASTUAICharacter>(GetOwner());
	if (!Character) return;
	
	Character->PlayAnimMontage(Character->Animation);
}

void ASTUFistWeapon::InitFX()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if(!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	
	SetMuzzleFXActive(true);
}

void ASTUFistWeapon::SetMuzzleFXActive(bool IsActive)
{
	if(MuzzleFXComponent)
    	{
    		//MuzzleFXComponent->SetPaused(!IsActive);
    		MuzzleFXComponent->SetVisibility(IsActive, true);
    	}
    
    	if(FireAudioComponent)
    	{
    		IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    	}
}

void ASTUFistWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	if(TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* ASTUFistWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
