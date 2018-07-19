// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// TODO protect against no patrol route component 

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	
	// set the patrolling guard ref and protect pointers 
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	
	// Get the patrol route component so we can get the waypoints using getter method 
	auto PatrolRouteComp = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComp)) { return EBTNodeResult::Failed; }

	auto Points = PatrolRouteComp->GetPoints();
	auto length = Points.Num();

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Points[Index]); // set the waypoint 
	//UE_LOG(LogTemp, Warning, TEXT("Index %i"), Index)

	// Cycle the index 
	auto NextIndex = (Index + 1) % length;
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	// finish execute 
	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::SetNextWayPoint(UBlackboardComponent* BlackboardComp)
{
		
		//auto Points = PatrollingGuardRef->GetPoints();
		//auto length = PatrollingGuardRef->GetPoints().Num();
		
		
		//BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Points[Index]);
		//UE_LOG(LogTemp, Warning, TEXT("Index %i"), Index)

		//auto NextIndex = (Index + 1) % length;
		//BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}


