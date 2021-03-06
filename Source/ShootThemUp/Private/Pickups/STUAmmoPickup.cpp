// Shoot Them Up Game. All rights reserved!


#include "Pickups/STUAmmoPickup.h"


#include "Components/STUHealthComponent.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUActorComponent<USTUHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTUActorComponent<USTUWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;
	
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
