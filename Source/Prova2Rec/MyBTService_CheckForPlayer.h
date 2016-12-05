// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "MyBTService_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROVA2REC_API UMyBTService_CheckForPlayer : public UBTService
{
	GENERATED_BODY()
	
public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
	
};
