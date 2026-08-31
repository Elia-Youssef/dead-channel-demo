// Project By Rebel Art Studios.


#include "UMG/HUDWidget.h"
#include "Animation/WidgetAnimation.h"
#include "UMG/HudFlashLight.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(RestartText) && IsValid(QuitText) && IsValid(LPText1Text) && IsValid(LPText2Text)
		&& IsValid(LPText3Text) && IsValid(LPText4Text) && IsValid(LPText5Text)
		&& IsValid(LPText6Text) && IsValid(LPText7Text))
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
	}

	ToggleCrosshair(false);
	ToggleInteractionText(false, FText::FromString(""));

	InitialTextColors();

	// The Widget Is Hidden At Begin Play
	// SetRenderOpacity(0.f);
}

void UHudWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Hud FlashLight Spawn 
}

void UHudWidget::InitialTextColors()
{
	if (!TextBlocks.IsEmpty())
	{
		for (UTextBlock* TextBlock : TextBlocks)
		{
			TextBlock->SetColorAndOpacity(StartColor);
		}
	}
}

UTextBlock* UHudWidget::GetActionText(EHudActions Action) const
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
	case EHudActions::Flashlight:
		return LPText5Text.Get();
	case EHudActions::Interact:
		return LPText6Text.Get();
	case EHudActions::Drone:
		return LPText7Text.Get();
	default:
		return nullptr;
	}
}

void UHudWidget::ToggleCrosshair(const bool bEnable)
{
	if (!IsValid(CrosshairImage)) return;

	CrosshairImage->SetVisibility(bEnable ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UHudWidget::ToggleInteractionText(const bool bEnable, const FText NewText)
{
	if (!IsValid(InteractionText)) return;

	InteractionText->SetText(bEnable ? NewText : FText::FromString(""));
	InteractionText->SetVisibility(bEnable ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UHudWidget::SwitchColor(EHudActions Action, bool bOn)
{
	if (UTextBlock* TargetText = GetActionText(Action); IsValid(TargetText))
	{
		TargetText->SetColorAndOpacity(bOn ? EndColor : StartColor);
	}
}

void UHudWidget::ToggleHudWidget(bool bEnable)
{
	if (!IsValid(CrosshairAnimation)) return;

	PlayAnimation(CrosshairAnimation, 0.f, 1,
	              bEnable ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse);
}

void UHudWidget::UpdateFlashlightBattery(float CurrentBattery, float MaxBattery)
{
	const float BatteryPercent = MaxBattery > KINDA_SMALL_NUMBER
		                             ? FMath::Clamp(CurrentBattery / MaxBattery, 0.f, 1.f) * 100.f
		                             : 0.f;

	if (IsValid(HudFlashLightComp))
	{
		HudFlashLightComp->UpdateLightWidget(BatteryPercent);
	}
}

void UHudWidget::UpdateFlashlightState(bool bIsOn)
{
	if (IsValid(HudFlashLightComp))
	{
		HudFlashLightComp->ToggleLightIcon(bIsOn);
	}
}
