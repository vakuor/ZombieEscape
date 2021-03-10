// Shoot Them Up Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"

#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "ZMBInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API UZMBInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZMBInventoryComponent();

	void UseMedKit();
	bool HasKey() const;
	bool UseKey();
	bool TryToAddItem(EZMBItemType Type, int Count);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory", meta = (ClampMin = "0.0"))
	int MedKitsCount = 0;
public:
	int32 GetMedKitsCount() const
	{
		//Count.Count = MedKitsCount;
		return MedKitsCount;
	}

	int32 GetKeysCount() const
	{
		//Count.Count = KeysCount;
		return KeysCount;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	int MedKitHealModifier = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	USoundCue* MedKitUseSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory", meta = (ClampMin = "0.0"))
	int KeysCount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	USoundCue* KeyUseSound;
private:
};
