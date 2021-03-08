// Shoot Them Up Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"

#include "STUBaseCharacter.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USoundCue;
class USphereComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()

public:
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float PickupDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	bool bRespawnable = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (EditCondition = "bRespawnable"));
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	bool Rotatable = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundCue* PickupTakenSound;
	
	//UPROPERTY(EditAnywhere, Category="Pickup")
	//bool CouldBeTakenTest = true;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;
private:
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;
	
	virtual bool GivePickupTo(APawn* PlayerPawn);

	void OnWorldUseEvent(const AController* Controller, FVector& Position);
	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();
};
