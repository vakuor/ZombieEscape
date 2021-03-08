// Shoot Them Up Game. All rights reserved!
#include "AI/Services/STUFireService.h"
#include "STUBaseCharacter.h"
#include "AIController.h"
#include "STUUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFireService, All, All)
USTUFireService::USTUFireService()
{
	NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	
	if(Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUActorComponent<USTUWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent)
		{
			if(HasAim)
			{
				
				WeaponComponent->StartFire();
			} 
			else
			{
				WeaponComponent->StopFire();
			}
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
