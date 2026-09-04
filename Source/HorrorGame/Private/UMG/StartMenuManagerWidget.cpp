// Project By Rebel Art Studios.


#include "UMG/StartMenuManagerWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Data/DataStructs.h"
#include "Components/VerticalBoxSlot.h"
#include "Frameworks/Controllers/StartMenuPlayerController.h"
#include "UMG/MenuButtonComponent.h"

void UStartMenuManagerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Create All Buttons 
	PopulateLevelButtons();
	PopulateActionButtons();

	// Animation Bindings
	FWidgetAnimationDynamicEvent FinishedEvent;
	FinishedEvent.BindDynamic(this, &UStartMenuManagerWidget::HandleWidgetAnimationFinished);
	BindToAnimationFinished(WidgetAnim, FinishedEvent);
}

void UStartMenuManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ForceDisableOpacity();
}

void UStartMenuManagerWidget::PopulateLevelButtons()
{
	if (!IsValid(LevelsVerticalBox) || !IsValid(LevelDataTable) || !IsValid(ButtonClass)) return;

	LevelsVerticalBox->ClearChildren();

	for (const FName& RowName : LevelDataTable->GetRowNames())
	{
		const FLevelData* LevelRow = LevelDataTable->FindRow<FLevelData>(RowName, TEXT("PopulateLevelButtons"));
		if (!LevelRow) continue;

		UMenuButtonComponent* NewLevelButton = CreateWidget<UMenuButtonComponent>(GetOwningPlayer(), ButtonClass);
		if (!NewLevelButton) continue;

		NewLevelButton->ButtonName = LevelRow->ButtonName;
		NewLevelButton->LevelReceivedName = LevelRow->LevelName;
		NewLevelButton->bOverrideName = false;

		NewLevelButton->ButtonLevel.BindUObject(this, &UStartMenuManagerWidget::CallSwitchLevel);
		if (UVerticalBoxSlot* ButtonSlot = LevelsVerticalBox->AddChildToVerticalBox(NewLevelButton))
		{
			ButtonSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 16.f));
		}
	}
}

void UStartMenuManagerWidget::PopulateActionButtons()
{
	if (IsValid(ExitButton))
		ExitButton->ButtonAction.AddUObject(this, &UStartMenuManagerWidget::CallExitGame);
}

void UStartMenuManagerWidget::ForceDisableOpacity()
{
	// RenderOpacity(0.f);
}

void UStartMenuManagerWidget::ToggleWidget(bool bToggle)
{
	if (!IsValid(WidgetAnim)) return;
	const EUMGSequencePlayMode::Type PlayMode = bToggle ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse;
	PlayAnimation(WidgetAnim, 0.f, 1, PlayMode);
}

void UStartMenuManagerWidget::CallExitGame()
{
	if (AStartMenuPlayerController* PC = GetOwningPlayer<AStartMenuPlayerController>())
		PC->CallExitLoop();
}

void UStartMenuManagerWidget::CallSwitchLevel(FName LevelName)
{
	if (AStartMenuPlayerController* PC = GetOwningPlayer<AStartMenuPlayerController>())
		PC->CallSwitchLevel(LevelName);
}

void UStartMenuManagerWidget::HandleWidgetAnimationFinished()
{
	// if (AStartMenuPlayerController* PC = GetOwningPlayer<AStartMenuPlayerController>())
	// 	PC->HandleMenuAnimationFinished();
}
