// Zombie Escape Game. All rights reserved!


#include "Pickups/ZMBKeyPickup.h"

#include "STUUtils.h"
#include "Components/ZMBInventoryComponent.h"

bool AZMBKeyPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUActorComponent<USTUHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;
	
	const auto InventoryComponent = STUUtils::GetSTUActorComponent<UZMBInventoryComponent>(PlayerPawn);
	if(!InventoryComponent) return false;
	
	return InventoryComponent->TryToAddItem(EZMBItemType::Key, Count);
}
