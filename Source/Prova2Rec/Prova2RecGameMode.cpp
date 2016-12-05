// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "Prova2RecGameMode.h"
#include "MyCharacter.h"
#include "MyHUD.h"

AProva2RecGameMode::AProva2RecGameMode() {

	HUDClass = AMyHUD::StaticClass();

	DefaultPawnClass = AMyCharacter::StaticClass();
	//DefaultPawnClass = NULL;


}
