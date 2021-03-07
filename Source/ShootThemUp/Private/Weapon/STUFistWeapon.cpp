// Shoot Them Up Game. All rights reserved!


#include "Weapon/STUFistWeapon.h"
#include "NiagaraComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Animations/AnimUtils.h"
#include "AI/STUAICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogFistWeapon, All, All)


void ASTUFistWeapon::StartFire()
{
	UE_LOG(LogFistWeapon, Display, TEXT("Vistrel kylaka"));
	MakeShot();
}


void ASTUFistWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ASTUFistWeapon::MakeShot()
{
	if(!GetWorld())
	{
		StopFire();
		return;
	}

	UGameplayStatics::ApplyRadialDamage(GetWorld(), WeaponDamage, GetActorLocation(), DamageRadius,
                                            UDamageType::StaticClass(), {GetOwner()}, this, GetController(), true);
	auto Character = Cast<ASTUAICharacter>(GetOwner());
	if (!Character) return;
	DrawDebugSphere(GetWorld(),GetActorLocation(),DamageRadius,24,FColor::Red,false,5.0f);
	Character->PlayRandomAttackAnimation();
	
}


AController* ASTUFistWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
