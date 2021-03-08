// Shoot Them Up Game. All rights reserved!


#include "Player/STUPlayerController.h"


#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "Components/STURespawnComponent.h"
#include "GameFramework/GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerController, All, All);

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
		}
	}
}

void ASTUPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	OnNewPawn.Broadcast(aPawn);
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
	InputComponent->BindAction("Use", IE_Pressed, this, &ASTUPlayerController::UseAction);
}

void ASTUPlayerController::OnPauseGame()
{
	UWorld* World = GetWorld();
	if(!World || !World->GetAuthGameMode()) return;
	World->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if(State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASTUPlayerController::OnMuteSound()
{
	if(!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if(!STUGameInstance) return;

	STUGameInstance->ToggleVolume();
}
//deprecated
void ASTUPlayerController::OnUseAction()
{
	UWorld* World = GetWorld();
	if(!World) return;
	
	const auto GameMode = Cast<ASTUGameModeBase>(World->GetAuthGameMode());
	if(!GameMode || !GetPawn()) return;
	FVector Location = GetPawn()->GetActorLocation();
	GameMode->OnUseActionInWorld.Broadcast(this, Location);
}

void ASTUPlayerController::UseAction()
{
	UWorld* World = GetWorld();
	if(!World) return;
	
	const auto GameMode = Cast<ASTUGameModeBase>(World->GetAuthGameMode());
	if(!GameMode) return;

	UE_LOG(LogSTUPlayerController, Display, TEXT("On Use Action"));
	GameMode->OnUseSignature.Broadcast(GetPawn());
}