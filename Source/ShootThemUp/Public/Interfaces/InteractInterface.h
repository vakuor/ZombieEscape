// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"


UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class SHOOTTHEMUP_API IInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	bool OnInteract(AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void StartFocus();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void EndFocus();

};
