// Project By Rebel Art Studios.


#include "UMG/MenuButtonComponent.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"


void UMenuButtonComponent::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateButton();
}

void UMenuButtonComponent::NativeConstruct()
{
	Super::NativeConstruct();
	BindActions();
	UpdateButton();
}

void UMenuButtonComponent::BindActions()
{
	if (IsValid(ButtonComp))
	{
		if (bOverrideName)
		{
			ButtonAction.AddUObject(this, &UMenuButtonComponent::HandleAction);
		}
		else
		{
			ButtonLevel.BindUObject(this, &UMenuButtonComponent::HandleLevel);
		}
		TextBlockComp->SetText(ButtonName);
	}
}

void UMenuButtonComponent::UpdateButton()
{
	if (!IsValid(SizeBoxComp)) return;

	SizeBoxComp->SetWidthOverride(ButtonSize.X);
	SizeBoxComp->SetHeightOverride(ButtonSize.Y);
}

void UMenuButtonComponent::HandleAction()
{
	ButtonAction.Broadcast();
}

void UMenuButtonComponent::HandleLevel(FName LevelName)
{
	ButtonLevel.ExecuteIfBound(LevelName);
}
