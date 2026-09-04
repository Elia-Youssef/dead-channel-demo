// Project By Rebel Art Studios.


#include "Frameworks/Controllers/StartMenuPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "UMG/StartMenuManagerWidget.h"

AStartMenuPlayerController::AStartMenuPlayerController()
{
}

void AStartMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FreezePlayer();
	SpawnMenu();
}

void AStartMenuPlayerController::SpawnMenu()
{
	if (!IsValid(MenuWidgetClass)) return;
	if (!IsValid(MenuWidgetPointer))
	{
		MenuWidgetPointer = CreateWidget<UStartMenuManagerWidget>(this, MenuWidgetClass);
		MenuWidgetPointer->SetVisibility(ESlateVisibility::Visible);
		MenuWidgetPointer->AddToViewport();
		MenuWidgetPointer->ForceDisableOpacity();
		WidgetTimer(true);
	}
}

void AStartMenuPlayerController::WidgetTimer(bool bPlayForward)
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer(WidgetTimerHandle, FTimerDelegate::CreateUObject(
		                                       this, &AStartMenuPlayerController::ToggleMenu, bPlayForward),
	                                       TimerDelay, false);
}


void AStartMenuPlayerController::ToggleMenu(bool bToggleWidget)
{
	MenuWidgetPointer->ToggleWidget(bToggleWidget);
}


void AStartMenuPlayerController::FreezePlayer()
{
	// Freeze Player
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);

	// Force Hide Mouse
	bShowMouseCursor = false;

	//Set Input Mode To UI Only
	const FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
}

void AStartMenuPlayerController::ToggleCursor(bool bToggle)
{
	bShowMouseCursor = bToggle;
}

void AStartMenuPlayerController::CameraFadeControl(EFadeType FadeType)
{
}

void AStartMenuPlayerController::CallExitLoop()
{
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}

void AStartMenuPlayerController::CallSwitchLevel(FName LevelName)
{
	OnLevelSwitchRequested.ExecuteIfBound(LevelName);
}

void AStartMenuPlayerController::InputModeTimer()
{
	if (!IsValid(GetWorld())) return;
	if (GetWorldTimerManager().IsTimerActive(InputModeTimerHandle)) return;

	GetWorldTimerManager().SetTimer(InputModeTimerHandle, FTimerDelegate::CreateUObject(this,
		                                &ThisClass::ToggleCursor, true), InputModeTimerDelay, false);
}
