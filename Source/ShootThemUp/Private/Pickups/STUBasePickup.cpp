// Shoot Them Up Game. All rights reserved!

#include "Pickups/STUBasePickup.h"


#include "STUGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);

	GenerateRotationYaw();
	
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnUseActionInWorld.AddUObject(this, &ASTUBasePickup::OnWorldUseEvent);
		}
	}
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
/*
	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
		PickupWasTaken();
	}*/
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Rotatable)
	{
		AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
	}
}

bool ASTUBasePickup::CouldBeTaken() const
{
	//return CouldBeTakenTest;
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTUBasePickup::OnWorldUseEvent(const AController* Controller, FVector& Position)
{
	if(!Controller || !Controller->GetPawn()) return;
	
	const auto Pawn = Cast<APawn>(Controller->GetPawn());
	//UE_LOG(LogBasePickup, Display, TEXT("Got position: %f"), Position.Size());
	UE_LOG(LogBasePickup, Display, TEXT("Dist: %f"), FVector::Distance(GetActorLocation(), Position));
	if (FVector::Distance(GetActorLocation(), Position) <= PickupDistance && GivePickupTo(Pawn))
	{
		UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
		PickupWasTaken();
	}
}

void ASTUBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
	
	if (bRespawnable)
	{
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
	}
	else
	{
		Destroy();
	}
	
}

void ASTUBasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

void ASTUBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
