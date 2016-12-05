// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Chaves.generated.h"

/**
 * 
 */
UCLASS()
class PROVA2REC_API AChaves : public AItem
{
	GENERATED_BODY()
	
public:
	AChaves();

	virtual int Use() override;

	
	
};
