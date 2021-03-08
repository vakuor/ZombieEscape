// Zombie Escape Game. All rights reserved!


#include "Interactables/ZMBHealthInteractiveActor.h"
#include "STUUtils.h"
#include "Components/ZMBInventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthInteractiveActor, All, All);


void AZMBHealthInteractiveActor::OnUse_Implementation(const AActor* Caller)
{
	if(!Caller) return;
	//UE_LOG(LogKeyInteractiveActor, Display, TEXT("OnUseImplementation2: %s"), *Caller->GetName());
	UZMBInventoryComponent* InventoryComponent = STUUtils::GetSTUActorComponent<UZMBInventoryComponent>(Caller);
	if(!InventoryComponent) return;
	//UE_LOG(LogKeyInteractiveActor, Display, TEXT("OnUseImplementation3"));
	
	FVector CallerPosition = Caller->GetActorLocation();
	//UE_LOG(LogKeyInteractiveActor, Display, TEXT("Dist: %f"), FVector::Distance(GetActorLocation(), CallerPosition));
	if (FVector::Distance(GetActorLocation(), CallerPosition) <= InteractDistance && InventoryComponent->TryToAddItem(EZMBItemType::MedKit, Count))
	{
		if(bPlaySoundOnInteract && InteractSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
		}
		UE_LOG(LogHealthInteractiveActor, Display, TEXT("Health actor has been interacted"));
		Destroy();
	}
}