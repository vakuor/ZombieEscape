// Zombie Escape Game. All rights reserved!


#include "Interactables/ZMBInteractiveActor.h"

#include "STUGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AZMBInteractiveActor::AZMBInteractiveActor()
{
 	PrimaryActorTick.bCanEverTick = false;
}

void AZMBInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnUseSignature.AddUObject(this, &AZMBInteractiveActor::OnUseExecute);
		}
	}
}

void AZMBInteractiveActor::OnUseExecute(const AActor* Caller)
{
	Execute_OnUse(this, Caller);
}
