// Shoot Them Up Game. All rights reserved!


#include "Components/ZMBInventoryComponent.h"


#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryComponent, All, All)

UZMBInventoryComponent::UZMBInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UZMBInventoryComponent::UseMedKit()
{
	const auto HealthComponent = STUUtils::GetSTUActorComponent<USTUHealthComponent>(GetOwner());
	if (!HealthComponent)
	{
		UE_LOG(LogInventoryComponent, Warning,
		       TEXT("No health component!"));
		return;
	}

	if (MedKitsCount <= 0)
	{
		UE_LOG(LogInventoryComponent, Display,
		       TEXT("Medkits count already: %d"), MedKitsCount);
		return;
	}

	if (HealthComponent->TryToAddHealth(MedKitHealModifier))
	{
		MedKitsCount--;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), MedKitUseSound, GetOwner()->GetActorLocation());
	
	}
	else
	{
		UE_LOG(LogInventoryComponent, Display, TEXT("Unable to add health!"));
	}
}

bool UZMBInventoryComponent::HasKey() const
{
	return KeysCount > 0 ? true : false;
}

bool UZMBInventoryComponent::UseKey()
{
	if (KeysCount <= 0)
	{
		UE_LOG(LogInventoryComponent, Display,
               TEXT("Keys count already: %d"), KeysCount);
		return false;
	}

	KeysCount--;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), KeyUseSound, GetOwner()->GetActorLocation());
	return true;
}

bool UZMBInventoryComponent::TryToAddItem(EZMBItemType Type, int Count)
{
	switch (Type)
	{
	case EZMBItemType::MedKit:
		{
			MedKitsCount += Count;
			break;
		}
	case EZMBItemType::Key:
		{
			KeysCount += Count;
			break;
		}
	default:
		{
			UE_LOG(LogInventoryComponent, Warning, TEXT("Reached default state in switch!"));
			return false;
		}
	}
	return true;
}
