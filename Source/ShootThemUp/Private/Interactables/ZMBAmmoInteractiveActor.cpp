// Zombie Escape Game. All rights reserved!


#include "Interactables/ZMBAmmoInteractiveActor.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"
#include "Components/ZMBInventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoInteractiveActor, All, All);

void AZMBAmmoInteractiveActor::OnUse_Implementation(const AActor* Caller)
{
	if(!Caller) return;

	UZMBInventoryComponent* InventoryComponent = STUUtils::GetSTUActorComponent<UZMBInventoryComponent>(Caller);
	if(!InventoryComponent) return;
	
	const auto WeaponComponent = STUUtils::GetSTUActorComponent<USTUWeaponComponent>(Caller);
	if(!WeaponComponent) return;
	
	UE_LOG(LogAmmoInteractiveActor, Display, TEXT("Ammo was taken"));
	
	FVector CallerPosition = Caller->GetActorLocation();
	if (FVector::Distance(GetActorLocation(), CallerPosition) <= InteractDistance)
	{
		if(WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount))
		{
			UE_LOG(LogAmmoInteractiveActor, Display, TEXT("Actor has been interacted"));
			Destroy();
		}
	}
}

