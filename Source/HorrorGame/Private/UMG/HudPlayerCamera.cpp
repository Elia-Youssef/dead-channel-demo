// Project By Rebel Art Studios.


#include "UMG/HudPlayerCamera.h"

#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"

void UHudPlayerCamera::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHudPlayerCamera::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleAnimation(true);
}

void UHudPlayerCamera::NativeDestruct()
{
	Super::NativeDestruct();

	ToggleAnimation(false);
}

void UHudPlayerCamera::ToggleAnimation(bool bToggle)
{
	if (!IsValid(IconBox) || !IsValid(CamIcon) || !IsValid(RecAnim)) return;
	PlayAnimation(RecAnim, 0.f, 0, EUMGSequencePlayMode::PingPong);
}
