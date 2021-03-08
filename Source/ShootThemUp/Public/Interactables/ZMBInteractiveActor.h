// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/UsableInterface.h"

#include "ZMBInteractiveActor.generated.h"

class USoundCue;

UCLASS()
class SHOOTTHEMUP_API AZMBInteractiveActor : public AActor, public IUsableInterface
{
private:
	GENERATED_BODY()

public:
	AZMBInteractiveActor();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float InteractDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	bool bPlaySoundOnInteract = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta = (EditCondition = "bPlaySoundOnInteract"))
	USoundCue* InteractSound;

private:
	void OnUseExecute(const AActor* Caller);
};
