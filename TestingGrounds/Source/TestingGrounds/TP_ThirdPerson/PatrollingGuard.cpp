// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingGuard.h"

TArray<AActor*> APatrollingGuard::GetPoints()
{
	for (AActor* Actor:PatrolPoints)
	{
		if (!ensure(Actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("No patrol points"))
		}
		//UE_LOG(LogTemp, Warning, TEXT("Patrol points, %s"), *Actor->GetName())

	}

	//auto Actor = *PatrolPoints.GetData();
	//auto Name = Actor->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Patrol points, %s"), *Name)
	return PatrolPoints;
}
