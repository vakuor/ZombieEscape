// Shoot Them Up Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"


#include "STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"

#include "STUPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetCurrentKeysCount() const;

	UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentMedKitsCount() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
    bool IsPlayerSpectator() const;
    
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnTakeDamage();
	
	UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category="UI")
    FString FormatBullets(int32 BulletsNum) const;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DamageAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FLinearColor GoodColor = FLinearColor::White;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FLinearColor BadColor = FLinearColor::Red;
	
    virtual void NativeOnInitialized() override;
	
private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
	void UpdateHealthBar();
};
