// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "Chaves.h"

AChaves::AChaves() {
	ConstructorHelpers::FObjectFinder<UStaticMesh>
		Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	if (Mesh.Succeeded()) {
		GetMeshComp()->SetStaticMesh(Mesh.Object);
	}
	GetMeshComp()->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
}

int AChaves::Use() {
	return FMath::RandRange(1, 10);
}




