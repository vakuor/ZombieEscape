// Zombie Escape Game. All rights reserved!


#include "Interactables/ZMBKeyInteractiveActor.h"
#include "STUUtils.h"
#include "Components/ZMBInventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogKeyInteractiveActor, All, All);

void AZMBKeyInteractiveActor::OnUse_Implementation(const AActor* Caller)
{
	if(!Caller) return;
	
	UZMBInventoryComponent* InventoryComponent = STUUtils::GetSTUActorComponent<UZMBInventoryComponent>(Caller);
	if(!InventoryComponent) return;
	
	FVector CallerPosition = Caller->GetActorLocation();
	if (FVector::Distance(GetActorLocation(), CallerPosition) <= InteractDistance && InventoryComponent->TryToAddItem(EZMBItemType::Key, Count))
	{
		UE_LOG(LogKeyInteractiveActor, Display, TEXT("Actor has been interacted"));
		Destroy();
	}
}
