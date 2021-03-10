// Shoot Them Up Game. All rights reserved!


#include "UI/STUGameOverWidget.h"

#include "STUGameModeBase.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"

void USTUGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
		}
	}

	if(ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
	}
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if(State == ESTUMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void USTUGameOverWidget::UpdatePlayersStat()
{
	if(!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();
	
	//for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	//{
		const auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);//It->Get();
		if(!Controller) return;//continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if(!PlayerState) return;//continue;
		
		const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) return;//continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
		//PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNum()));
		//PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
		//PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		//PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());
		
		PlayerStatBox->AddChild(PlayerStatRowWidget);
	//}
}

void USTUGameOverWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}