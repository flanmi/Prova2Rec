// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "PontoFinal.h"


// Sets default values
APontoFinal::APontoFinal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>
		AlavancaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
	if (AlavancaMesh.Succeeded()) {
		MeshComp->SetStaticMesh(AlavancaMesh.Object);
	}
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void APontoFinal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APontoFinal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

