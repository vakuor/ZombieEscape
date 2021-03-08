// Zombie Escape Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUsableInterface : public UInterface
{
	GENERATED_BODY()
};

class SHOOTTHEMUP_API IUsableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void OnUse(const AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    bool CanBeUsed(const AActor* Caller);
};
