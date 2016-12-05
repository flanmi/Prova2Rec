// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class PROVA2REC_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* Behavior;


	



private:
	UPROPERTY(EditAnywhere)
	USphereComponent* Root;
		UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;


		UPROPERTY(EditAnywhere)
			float DamageAmount = 1.0f;
		UFUNCTION()
			void OnHit(UPrimitiveComponent* HitComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

		UFUNCTION()
			void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
