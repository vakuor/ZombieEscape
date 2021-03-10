// Shoot Them Up Game. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FText& Text);
	void SetKills(const FText& Text);
	//void SetDeaths(const FText& Text);
	//void SetTeam(const FText& Text);
	//void SetPlayerIndicatorVisibility(bool Visible);
	//void SetTeamColor(const FLinearColor& Color);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsTextBlock;

	/*UPROPERTY(meta = (BindWidget))
<<<<<<< Updated upstream
	UTextBlock* DeathsTextBlock;*/
=======
	UTextBlock* DeathsTextBlock;
>>>>>>> Stashed changes

	/*UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTextBlock;*/

	/*UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;*/

<<<<<<< Updated upstream
	/*UPROPERTY(meta = (BindWidget))
=======
	UPROPERTY(meta = (BindWidget))
>>>>>>> Stashed changes
	UImage* TeamImage;*/
};


