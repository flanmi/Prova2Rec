// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "MyCharacter.h"
#include "Projetil.h"
#include "Item.h"
#include "PontoFinal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h" 



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -80.0f));
	GetMesh()->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		AnimObj(TEXT("AnimBlueprint'/Game/Blueprint/NewAnimBlueprint.NewAnimBlueprint'"));
	if (AnimObj.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimObj.Object->GetAnimBlueprintGeneratedClass());
	}

	ConstructorHelpers::FObjectFinder<UAnimSequence>
		AnimJumpLoad(TEXT("AnimSequence'/Game/AnimStarterPack/Jump_From_Stand.Jump_From_Stand'"));
	if (AnimJumpLoad.Succeeded()) {
		JumpAnim = AnimJumpLoad.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimSequence>
		AnimCrouchLoad(TEXT("AnimSequence'/Game/AnimStarterPack/Crouch_Idle_Rifle_Hip.Crouch_Idle_Rifle_Hip'"));
	if (AnimJumpLoad.Succeeded()) {
		CrouchAnim = AnimJumpLoad.Object;
	}



	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	PlayerCamera->AttachTo(CameraBoom);

	CollectCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollectCollision"));
	CollectCollisionComp->InitSphereRadius(200.0f);
	CollectCollisionComp->AttachTo(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;


	ConstructorHelpers::FObjectFinder<USoundCue>SoundCue(TEXT("SoundCue'/Game/Audios/13922__adcbicycle__18_Cue.13922__adcbicycle__18_Cue'"));
	if (SoundCue.Succeeded()) {
		ItemSound = SoundCue.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundCue>SoundCue2(TEXT("SoundCue'/Game/Audios/13996__adcbicycle__44_Cue.13996__adcbicycle__44_Cue'"));
	if (SoundCue2.Succeeded()) {
		DepositSound = SoundCue2.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundCue>SoundCue3(TEXT("SoundCue'/Game/Audios/Ta_Da-SoundBible_com-1884170640_Cue.Ta_Da-SoundBible_com-1884170640_Cue'"));
	if (SoundCue3.Succeeded()) {
		VictorySound = SoundCue3.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundCue>SoundCue4(TEXT("SoundCue'/Game/Audios/shoot_Cue.shoot_Cue'"));
	if (SoundCue4.Succeeded()) {
		FireSound = SoundCue4.Object;
	}
	AudioComp = CreateDefaultSubobject<UAudioComponent>	(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	AudioComp->AttachTo(GetMesh());
	
	







	
	bReplicates = true;
	bReplicateMovement = true;




}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode
		&& GetCharacterMovement()->IsMovingOnGround()) {
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	InputComponent->BindAxis("TurnRate", this, &AMyCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
	InputComponent->BindAxis("LookUpRate", this, &AMyCharacter::LookUpAtRate);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::StartCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouch);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::Pause);
	InputComponent->BindAction("Drop", IE_Pressed, this, &AMyCharacter::DropProjectile);

	InputComponent->BindAction("Collect", IE_Pressed, this, &AMyCharacter::OnCollect);

	bReplicates = true;
	bReplicateMovement = true;
}



void AMyCharacter::MoveForward(float Value) {
	if (Controller != nullptr && Value != 0) {
		FRotator Rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround()) {
			Rotation.Pitch = 0.0f;
		}
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void AMyCharacter::MoveRight(float Value) {
	if (Controller != nullptr && Value != 0.0f) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
void AMyCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void AMyCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
void AMyCharacter::StartRun() {

		GetCharacterMovement()->MaxWalkSpeed = 800;
}

void AMyCharacter::StopRun() {

	GetCharacterMovement()->MaxWalkSpeed = 400;
}
void AMyCharacter::StartCrouch() {
	Crouch();
	if (CrouchAnim != nullptr) {
		GetMesh()->PlayAnimation(CrouchAnim, false);
	}
}
void AMyCharacter::StopCrouch() {
	UnCrouch();
}

void AMyCharacter::Turn(float Value) {
	AddControllerYawInput(Value);
}
void AMyCharacter::LookUp(float Value) {
	AddControllerPitchInput(Value);
}

void AMyCharacter::Jump() {
	Super::Jump();

	if (JumpAnim != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim, false);
	}
}


	


void AMyCharacter::DropProjectile() {
	//if (Role == ROLE_Authority) {
	DropProjectileServer();
	//}
}

void AMyCharacter::DropProjectileServer_Implementation() {
	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();
	if (World != nullptr) {
		FRotator Rotation = GetMesh()->GetComponentRotation();
		Rotation.Yaw -= -90.f;
		AProjetil* Proj = World->SpawnActor<AProjetil>(GetActorLocation(), Rotation, SpawnParameters);
		AudioComp->SetSound(FireSound);
		AudioComp->Play();
		if (Proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Spawn OK!"));
		}
	}
}

bool AMyCharacter::DropProjectileServer_Validate() {
	return true;
}



void AMyCharacter::SetLife(int NewLife) {
	Life = NewLife;
}
int AMyCharacter::GetLife() {
	return Life;
}


void AMyCharacter::OnDeath() {
	if (Life <= 0) {
		FVector InitialLocation(-80.0f, 1090.0f, 292.0f);
		Life = 3;
		SetActorLocation(InitialLocation);

	}

}

void AMyCharacter::Vitoria() {
	if (ItemCaixa >= 7) {
		AudioComp->SetSound(VictorySound);
		AudioComp->Play();
	}

}

/*void AMyCharacter::OnCollect() {
	TArray<AActor*> AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	for (int i = 0; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(AItem::StaticClass()) ) {
			AItem* ItemColetado = Cast<AItem>(AtoresColetados[i]);
			Inventory.Add(ItemColetado);
			ItemColetado->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("%d"), Inventory.Num());
		}
	}
}*/

void AMyCharacter::OnCollect() {
	
	TArray<AActor*> AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	for (int i = 0; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(AItem::StaticClass()) && (ItemChave == 0)) {
			AItem* ItemColetado = Cast<AItem>(AtoresColetados[i]);
			Inventory.Add(ItemColetado);
			AudioComp->SetSound(ItemSound);
			AudioComp->Play();
			ItemChave++;
			ItemColetado->Destroy();
			
		}
		else if (AtoresColetados[i]->IsA(APontoFinal::StaticClass()) && (ItemChave != 0)) {
			AudioComp->SetSound(DepositSound);
			AudioComp->Play();
			ItemChave--;
			ItemCaixa++;
			Vitoria();
		}
	}
}


