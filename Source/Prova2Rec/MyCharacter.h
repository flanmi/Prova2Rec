// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROVA2REC_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		float BaseTurnRate;
	

	void SetLife(int NewLife);
	int GetLife();
	void OnDeath();

	FORCEINLINE TArray<class AItem*> GetInventory() const { return Inventory; }

	FORCEINLINE int GetNewItemChave() const { return ItemChave; }
	FORCEINLINE void AMyCharacter::SetNewItemChave(int NewItemChave) { ItemChave = NewItemChave; }
	FORCEINLINE int GetNewItemCaixa() const { return ItemCaixa; }
	FORCEINLINE void AMyCharacter::SetNewItemCaixa(int NewItemCaixa) { ItemChave = NewItemCaixa; }

	
	void Vitoria();

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		int ItemChave = 0;
	UPROPERTY(EditAnywhere)
		int ItemCaixa = 0;

	UPROPERTY(EditAnywhere)
		UAnimSequence* JumpAnim;
	UPROPERTY(EditAnywhere)
		UAnimSequence* CrouchAnim;



	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartRun();
	void StopRun();
	void Turn(float Value);
	void LookUp(float Value);
	void LookUpAtRate(float Rate);
	void TurnAtRate(float Rate);
	void StartCrouch();
	void StopCrouch();
	void DropProjectile();
	void OnCollect();
	void Pause();
	void Jump();

	


	UFUNCTION(Reliable, Server, WithValidation)
	void DropProjectileServer();
	void DropProjectileServer_Implementation();
	bool DropProjectileServer_Validate();



	UPROPERTY(EditAnywhere)
		int Life = 3;

	USphereComponent* CollectCollisionComp;
	TArray<class AItem*> Inventory;
	TSubclassOf<class UUserWidget> UserWidget;


	USoundCue* DepositSound;
	USoundCue* ItemSound;
	USoundCue* VictorySound;
	USoundCue* FireSound;
	UAudioComponent* AudioComp;





};
