// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "AIController.h"
#include "TestingGrounds/TP_ThirdPerson/PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	
	// set the patrolling guard ref and protect pointers 
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	PatrollingGuardRef = Cast<APatrollingGuard>(ControlledPawn);
	if (!ensure(PatrollingGuardRef)) { UE_LOG(LogTemp, Warning, TEXT("No patroller")) }

	SetNextWayPoint(BlackboardComp);

	// finish execute 
	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::SetNextWayPoint(UBlackboardComponent* BlackboardComp)
{
		auto Points = PatrollingGuardRef->GetPoints();
		auto length = PatrollingGuardRef->GetPoints().Num();
		
		
		BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Points[Index]);
		UE_LOG(LogTemp, Warning, TEXT("Index %i"), Index)

		auto NextIndex = (Index + 1) % length;
		BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}


