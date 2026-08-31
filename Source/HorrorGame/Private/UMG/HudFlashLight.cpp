// Project By Rebel Art Studios.

#include "UMG/HudFlashLight.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"

void UHudFlashLight::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateSizeBox();
}

void UHudFlashLight::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHudFlashLight::ToggleLightIcon(bool bEnable)
{
	bIsLightEnabled = bEnable;
	UpdateLightIconColor(LastBatteryProgress);
}

void UHudFlashLight::UpdateLightWidget(float Progress)
{
	LastBatteryProgress = FMath::Clamp(Progress, 0.f, 100.f);
	UpdateLightScrollBar(LastBatteryProgress);
	UpdateLightIconColor(LastBatteryProgress);
}

void UHudFlashLight::UpdateLightScrollBar(float Progress)
{
	const int CurrentProgress = FMath::Clamp(FMath::FloorToInt(Progress), 0, 100);
	if (FlashLightScrollBar) FlashLightScrollBar->SetPercent(static_cast<float>(CurrentProgress) / 100.f);
}

void UHudFlashLight::UpdateLightIconColor(float Progress)
{
	if (!IsValid(FlashLightImage)) return;

	if (!bIsLightEnabled)
	{
		FlashLightImage->SetColorAndOpacity(LightOffColor);
		return;
	}

	const float Alpha = FMath::Clamp(Progress / 100.f, 0.f, 1.f);
	const FLinearColor CurrentColor = FMath::Lerp(LightLowColor, LightOnColor, Alpha);
	FlashLightImage->SetColorAndOpacity(CurrentColor);
}

void UHudFlashLight::UpdateSizeBox()
{
	if (LightIconBox)
	{
		LightIconBox->SetWidthOverride(LightIconSize.X);
		LightIconBox->SetHeightOverride(LightIconSize.Y);
	}
}
