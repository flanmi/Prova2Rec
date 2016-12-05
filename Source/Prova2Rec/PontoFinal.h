// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PontoFinal.generated.h"

UCLASS()
class PROVA2REC_API APontoFinal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APontoFinal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	UStaticMeshComponent* MeshComp;

	
};
