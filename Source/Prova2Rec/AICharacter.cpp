// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "AICharacter.h"
#include "MyCharacter.h"
#include "Projetil.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));

	Root->SetCollisionProfileName("BlockAll");
	Root->OnComponentHit.AddDynamic(this, &AAICharacter::OnHit);
	Root->bGenerateOverlapEvents = true;
	Root->SetCollisionProfileName("OverlapAllDynamic");
	Root->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnOverlapBegin);

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);

	}
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldLocation(FVector(.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}







void AAICharacter::OnHit(UPrimitiveComponent* HitComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	/*if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT"));
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		MyCharacter->SetLife(MyCharacter->GetLife() - DamageAmount);
		MyCharacter->OnDeath();
		UE_LOG(LogTemp, Warning, TEXT("Life = %d"), MyCharacter->GetLife());


	}

	else if ((OtherActor != nullptr) && (OtherActor != this) && (OtherActor->IsA(AProjetil::StaticClass())) && (OtherComp != nullptr))
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("acertou"));
	}*/


}

void AAICharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherActor->IsA(AProjetil::StaticClass())) && (OtherComp != nullptr))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("acertou"));
		Destroy();
	}


	else if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT"));
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		MyCharacter->SetLife(MyCharacter->GetLife() - DamageAmount);
		MyCharacter->OnDeath();
		UE_LOG(LogTemp, Warning, TEXT("Life = %d"), MyCharacter->GetLife());


	}


}