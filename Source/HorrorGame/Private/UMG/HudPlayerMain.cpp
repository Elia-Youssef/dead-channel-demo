// Project By Rebel Art Studios.


#include "UMG/HudPlayerMain.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UMG/HudFlashLight.h"

void UHudPlayerMain::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(RestartText) && IsValid(QuitText) && IsValid(LPText1Text) && IsValid(LPText2Text)
		&& IsValid(LPText3Text) && IsValid(LPText4Text) && IsValid(LPText5Text)
		&& IsValid(LPText6Text) && IsValid(LPText7Text) && IsValid(LPText8Text))
	{
		TextBlocks.Empty();
		TextBlocks.AddUnique(RestartText);
		TextBlocks.AddUnique(QuitText);
		TextBlocks.AddUnique(LPText1Text);
		TextBlocks.AddUnique(LPText2Text);
		TextBlocks.AddUnique(LPText3Text);
		TextBlocks.AddUnique(LPText4Text);
		TextBlocks.AddUnique(LPText5Text);
		TextBlocks.AddUnique(LPText6Text);
		TextBlocks.AddUnique(LPText7Text);
		TextBlocks.AddUnique(LPText8Text);
	}

	ToggleCrosshair(false);
	ToggleInteractionText(false, FText::GetEmpty());
	InitialTextColors();
}

void UHudPlayerMain::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHudPlayerMain::InitialTextColors()
{
	for (UTextBlock* TextBlock : TextBlocks)
	{
		if (IsValid(TextBlock))
		{
			TextBlock->SetColorAndOpacity(StartColor);
		}
	}
}

UTextBlock* UHudPlayerMain::GetActionText(EHudActions Action) const
{
	switch (Action)
	{
	case EHudActions::Move:
		return LPText1Text.Get();
	case EHudActions::Restart:
		return RestartText.Get();
	case EHudActions::Quit:
		return QuitText.Get();
	case EHudActions::Sprint:
		return LPText2Text.Get();
	case EHudActions::Jump:
		return LPText3Text.Get();
	case EHudActions::ChangeView:
		return LPText4Text.Get();
	case EHudActions::PlayerCamView:
		return LPText5Text.Get();
	case EHudActions::Flashlight:
		return LPText6Text.Get();
	case EHudActions::Interact:
		return LPText7Text.Get();
	case EHudActions::Drone:
		return LPText8Text.Get();
	default:
		return nullptr;
	}
}

void UHudPlayerMain::ToggleCrosshair(bool bEnable)
{
	if (IsValid(CrosshairImage))
	{
		CrosshairImage->SetVisibility(bEnable ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UHudPlayerMain::ToggleInteractionText(bool bEnable, FText NewText)
{
	if (IsValid(InteractionText))
	{
		InteractionText->SetText(bEnable ? NewText : FText::GetEmpty());
		InteractionText->SetVisibility(bEnable ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UHudPlayerMain::SwitchColor(EHudActions Action, bool bOn)
{
	if (UTextBlock* TargetText = GetActionText(Action))
	{
		TargetText->SetColorAndOpacity(bOn ? EndColor : StartColor);
	}
}

void UHudPlayerMain::ToggleHudWidget(bool bEnable)
{
}

void UHudPlayerMain::UpdateFlashlightBattery(float CurrentBattery, float MaxBattery)
{
	const float BatteryPercent = MaxBattery > KINDA_SMALL_NUMBER
		                             ? FMath::Clamp(CurrentBattery / MaxBattery, 0.f, 1.f) * 100.f
		                             : 0.f;

	if (IsValid(HudFlashLightComp))
	{
		HudFlashLightComp->UpdateLightWidget(BatteryPercent);
	}
}

void UHudPlayerMain::UpdateFlashlightState(bool bIsOn)
{
	if (IsValid(HudFlashLightComp))
	{
		HudFlashLightComp->ToggleLightIcon(bIsOn);
	}
}
