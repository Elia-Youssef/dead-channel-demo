// Project By Rebel Art Studios.


#include "UMG/HudManagerWidget.h"
#include "Components/WidgetSwitcher.h"
#include "UMG/HudPlayerCamera.h"
#include "UMG/HudPlayerMain.h"

void UHudManagerWidget::SwitchMenus(ESwitchMenus Menu)
{
	if (!IsValid(HudSwitcher)) return;

	switch (Menu)
	{
	case ESwitchMenus::MainHud:
	default:
		if (IsValid(HudPlayerMain))
		{
			HudSwitcher->SetActiveWidget(HudPlayerMain);
		}
		break;

	case ESwitchMenus::CameraHud:
		if (IsValid(HudPlayerCam))
		{
			HudSwitcher->SetActiveWidget(HudPlayerCam);
		}
		break;
	}
}

UHudPlayerMain* UHudManagerWidget::GetPlayerMainHud() const
{
	return HudPlayerMain.Get();
}

UHudPlayerCamera* UHudManagerWidget::GetPlayerCam() const
{
	return HudPlayerCam.Get();
}

void UHudManagerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SwitchMenus(ESwitchMenus::MainHud);
}

void UHudManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SwitchMenus(ESwitchMenus::MainHud);
}
