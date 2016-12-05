// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "Projetil.h"
#include "AICharacter.h"


// Sets default values
AProjetil::AProjetil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));

	Root->bGenerateOverlapEvents = true;
	Root->SetCollisionProfileName("OverlapAllDynamic");
	Root->OnComponentBeginOverlap.AddDynamic(this, &AProjetil::OnOverlapBegin);
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	MeshComp->AttachTo(RootComponent);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Root;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;

	InitialLifeSpan = 5.0f;



}

// Called when the game starts or when spawned
void AProjetil::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultZ = GetActorLocation().Z;
}

// Called every frame
void AProjetil::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector Location = GetActorLocation();
	Location.Z = DefaultZ;
	SetActorLocation(Location);
}


void AProjetil::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	/*if ((OtherActor != nullptr) && (OtherActor != this) && (OtherActor->IsA(AAICharacter::StaticClass())) && (OtherComp != nullptr))
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("acertou"));
	}
	*/




}