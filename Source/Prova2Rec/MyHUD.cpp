// Fill out your copyright notice in the Description page of Project Settings.

#include "Prova2Rec.h"
#include "MyHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

AMyHUD::AMyHUD() {
	static ConstructorHelpers::FObjectFinder<UFont>
		Font(TEXT("Font'/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField'"));
	if (Font.Succeeded()) {
		HUDFont = Font.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>Texture(TEXT("Texture2D'/Game/Textures/heart.heart'"));
	if (Texture.Succeeded()) {
		Life = Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>ChaveTexture(TEXT("Texture2D'/Game/Textures/key.key'"));
	if (ChaveTexture.Succeeded()) {
		Chave = ChaveTexture.Object;
	}
}

void AMyHUD::DrawHUD() {
	Super::DrawHUD();

	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX,
		Canvas->SizeY);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(	UGameplayStatics::GetPlayerPawn(this, 0));

	FString LifeString = FString::Printf(TEXT("Life: "),MyCharacter->GetLife());
	DrawText(LifeString, FColor::Red, 50, 50, HUDFont);

	FString CoinString = FString::Printf(TEXT("Keys: %d/7"), MyCharacter->GetNewItemCaixa());
	DrawText(CoinString, FColor::Yellow, 50, 70, HUDFont);

	if (MyCharacter->GetLife() == 0) {
		FString Fim = FString::Printf(TEXT("GAME OVER"));
		DrawText(Fim, FColor::Red, 180, 180, HUDFont);
	}



	if (MyCharacter->GetLife() == 3) {
		DrawTextureSimple(Life, 200, 50, 1.0f, false);
		DrawTextureSimple(Life, 230, 50, 1.0f, false);
		DrawTextureSimple(Life, 260, 50, 1.0f, false);
	}
	else if (MyCharacter->GetLife() == 2) {
		DrawTextureSimple(Life, 200, 50, 1.0f, false);
		DrawTextureSimple(Life, 230, 50, 1.0f, false);
	}
	else if (MyCharacter->GetLife() == 1) {
		DrawTextureSimple(Life, 200, 50, 1.0f, false);
	}




	if (MyCharacter->GetNewItemChave() == 1) {

		DrawTextureSimple(Chave, ScreenDimensions.X - Chave->GetSizeX() * 2, 50, 1.0f, false);

	}
	
}

