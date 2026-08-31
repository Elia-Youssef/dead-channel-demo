// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils.generated.h"

USTRUCT()
struct FEmissiveProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<int32, UMaterialInterface*> EmissiveMat;

	UPROPERTY(EditAnywhere)
	FLinearColor EmissiveColor = FLinearColor::White;

	UPROPERTY(EditAnywhere)
	float EmissiveIntensity = 0.f;
};

USTRUCT()
struct FLightProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bToggleLight = true;

	UPROPERTY(EditAnywhere)
	bool bToggleShadows = true;

	UPROPERTY(EditAnywhere)
	bool bUseTemperature = true;

	UPROPERTY(EditAnywhere)
	float LightIntensity = 1.f;

	UPROPERTY(EditAnywhere)
	float LightAttenuation = 1000.f;

	UPROPERTY(EditAnywhere)
	float LightTemp = 1000.f;

	UPROPERTY(EditAnywhere)
	FLinearColor LightColor = FLinearColor::White;

	UPROPERTY(EditAnywhere)
	float InnerCone = 1.f;

	UPROPERTY(EditAnywhere)
	float OuterCone = 50.f;

	UPROPERTY(EditAnywhere)
	float SpecIntensity = 50.f;
};
