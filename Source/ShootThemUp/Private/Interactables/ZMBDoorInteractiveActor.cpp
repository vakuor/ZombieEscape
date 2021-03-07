// Zombie Escape Game. All rights reserved!


#include "Interactables/ZMBDoorInteractiveActor.h"

#include "STUGameModeBase.h"
#include "STUUtils.h"
#include "Components/ZMBInventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogDoorInteractiveActor, All, All);

void AZMBDoorInteractiveActor::OnUse_Implementation(const AActor* Caller)
{
	if(!Caller) return;
	
	UZMBInventoryComponent* InventoryComponent = STUUtils::GetSTUActorComponent<UZMBInventoryComponent>(Caller);
	if(!InventoryComponent) return;
	
	FVector CallerPosition = Caller->GetActorLocation();
	if (FVector::Distance(GetActorLocation(), CallerPosition) <= InteractDistance && InventoryComponent->UseKey())
	{
		UE_LOG(LogDoorInteractiveActor, Display, TEXT("Actor has been interacted"));
		Open();
	}
}

void AZMBDoorInteractiveActor::Open()
{
	UWorld* World = GetWorld();
	if(!World) return;
	
	const auto GameMode = Cast<ASTUGameModeBase>(World->GetAuthGameMode());
	if(!GameMode) return;

	UE_LOG(LogDoorInteractiveActor, Display, TEXT("On Door Open"));
	GameMode->OnExitUnlocked.Broadcast();
}

