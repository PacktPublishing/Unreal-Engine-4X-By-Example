// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMode.h"
#include "BMHUD.h"


ABMHUD::ABMHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}


void ABMHUD::DrawHUD()
{
	Super::DrawHUD();

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY *0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f)),
										  (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));


	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition,
						     CrosshairTex->Resource,
							 FLinearColor::White);

	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
