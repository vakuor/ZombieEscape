// Shoot Them Up Game. All rights reserved!


#include "UI/STUPlayerStatRowWidget.h"


#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}
<<<<<<< Updated upstream
/*
void USTUPlayerStatRowWidget::SetDeaths(const FText& Text)
=======

/*void USTUPlayerStatRowWidget::SetDeaths(const FText& Text)
>>>>>>> Stashed changes
{
	if(!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}*/

/*void USTUPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if(!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}*/
/*
void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if(!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if(!TeamImage) return;
	TeamImage->SetColorAndOpacity(Color);
<<<<<<< Updated upstream
}*/
=======
}
*/
>>>>>>> Stashed changes
