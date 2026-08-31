// Project By Rebel Art Studios.


#include "HorrorGame/Public/Frameworks/HorrorPlayerController.h"

#include "Actors/BaseSecCam.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Frameworks/HorrorBaseCharacter.h"
#include "Frameworks/FlashLightComponent.h"
#include "GameFramework/Character.h"
#include "UMG/HudWidget.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AHorrorPlayerController::AHorrorPlayerController()
{
}

void AHorrorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(HudWidgetClass) && !IsValid(HudWidgetComp))
	{
		HudWidgetComp = CreateWidget<UHudWidget>(this, HudWidgetClass);
		HudWidgetComp->AddToViewport();
	}

	BindFlashLightComponent();
}

void AHorrorPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BindFlashLightComponent();
}

void AHorrorPlayerController::BindFlashLightComponent()
{
	AHorrorBaseCharacter* OwnedCharacter = Cast<AHorrorBaseCharacter>(GetPawn());
	UFlashLightComponent* NewFlashLightComp = OwnedCharacter ? OwnedCharacter->GetFlashLightComponent() : nullptr;

	if (BoundFlashLightComp.Get() != NewFlashLightComp)
	{
		if (IsValid(BoundFlashLightComp))
		{
			BoundFlashLightComp->OnBatteryChanged.RemoveDynamic(this, &AHorrorPlayerController::HandleFlashLightBatteryChanged);
			BoundFlashLightComp->OnFlashLightStateChanged.RemoveDynamic(this, &AHorrorPlayerController::HandleFlashLightStateChanged);
		}

		BoundFlashLightComp = NewFlashLightComp;

		if (IsValid(BoundFlashLightComp))
		{
			BoundFlashLightComp->OnBatteryChanged.AddDynamic(this, &AHorrorPlayerController::HandleFlashLightBatteryChanged);
			BoundFlashLightComp->OnFlashLightStateChanged.AddDynamic(this, &AHorrorPlayerController::HandleFlashLightStateChanged);
		}
	}

	if (IsValid(BoundFlashLightComp))
	{
		HandleFlashLightBatteryChanged(BoundFlashLightComp->CurrentBattery, BoundFlashLightComp->MaxBattery);
		HandleFlashLightStateChanged(BoundFlashLightComp->bOn);
	}
}

void AHorrorPlayerController::HandleFlashLightBatteryChanged(float CurrentBattery, float MaxBattery)
{
	if (IsValid(HudWidgetComp))
	{
		HudWidgetComp->UpdateFlashlightBattery(CurrentBattery, MaxBattery);
	}
}

void AHorrorPlayerController::HandleFlashLightStateChanged(bool bIsOn)
{
	if (IsValid(HudWidgetComp))
	{
		HudWidgetComp->UpdateFlashlightState(bIsOn);
	}
}

void AHorrorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_HorrorGame, 0);
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(IA_Restart, ETriggerEvent::Started, this, &AHorrorPlayerController::Restart_Action);
		EIC->BindAction(IA_Quit, ETriggerEvent::Started, this, &AHorrorPlayerController::Quit_Action);

		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AHorrorPlayerController::Move_Action);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AHorrorPlayerController::Look_Action);

		EIC->BindAction(IA_Focus, ETriggerEvent::Started, this, &AHorrorPlayerController::Focus_Start_Action);
		EIC->BindAction(IA_Focus, ETriggerEvent::Completed, this, &AHorrorPlayerController::Focus_Stop_Action);
		EIC->BindAction(IA_Focus, ETriggerEvent::Canceled, this, &AHorrorPlayerController::Focus_Stop_Action);

		EIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AHorrorPlayerController::Crouch_Start_Action);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AHorrorPlayerController::Crouch_Stop_Action);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Canceled, this, &AHorrorPlayerController::Crouch_Stop_Action);

		EIC->BindAction(IA_Run, ETriggerEvent::Started, this, &AHorrorPlayerController::Run_Start_Action);
		EIC->BindAction(IA_Run, ETriggerEvent::Completed, this, &AHorrorPlayerController::Run_Stop_Action);
		EIC->BindAction(IA_Run, ETriggerEvent::Canceled, this, &AHorrorPlayerController::Run_Stop_Action);

		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AHorrorPlayerController::Jump_Action);

		EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &AHorrorPlayerController::Interact_Action);

		EIC->BindAction(IA_Flashlight, ETriggerEvent::Started, this, &AHorrorPlayerController::Flashlight_Action);

		EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &AHorrorPlayerController::ChangeView_Action);

		EIC->BindAction(IA_Drone, ETriggerEvent::Started, this, &AHorrorPlayerController::Drone_Action);
	}
}

void AHorrorPlayerController::CameraFadeControl(EFadeType FadeType)
{
	APlayerCameraManager* Manager = PlayerCameraManager;
	if (!IsValid(Manager)) return;

	switch (FadeType)
	{
	case EFadeType::FadeBlack:
		Manager->SetManualCameraFade(1.f, FLinearColor::Black, true);
		break;

	case EFadeType::FadeClear:
		Manager->SetManualCameraFade(0.f, FLinearColor::Black, true);
		break;

	case EFadeType::FadeIn:
		Manager->StartCameraFade(0.f, 1.f, 2.f, FLinearColor::Black, true);
		break;

	case EFadeType::FadeOut:
		Manager->StartCameraFade(1.f, 0.f, 2.f, FLinearColor::Black, true);
		break;
	default: break;
	}
}


void AHorrorPlayerController::Move_Action(const FInputActionValue& Value)
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(OwnedPawn))
		{
			MyChar->HandleMove(Value.Get<FVector2D>());
		}
	}
}

void AHorrorPlayerController::Look_Action(const FInputActionValue& Value)
{
	if (ABaseSecCam* SecurityCamera = Cast<ABaseSecCam>(GetPawn()))
	{
		SecurityCamera->PanAround(Value.Get<FVector2D>());
	}
	else if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(GetPawn()))
	{
		MyChar->HandleLook(Value.Get<FVector2D>());
	}
}

void AHorrorPlayerController::Focus_Start_Action()
{
	if (ABaseSecCam* SecurityCamera = Cast<ABaseSecCam>(GetPawn()))
	{
		SecurityCamera->ZoomAround(true);
		return;
	}

	if (HudWidgetComp) HudWidgetComp->ToggleCrosshair(true);

	if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(GetPawn()))
	{
		MyChar->FocusControl(true);
	}
}

void AHorrorPlayerController::Focus_Stop_Action()
{
	if (ABaseSecCam* SecurityCamera = Cast<ABaseSecCam>(GetPawn()))
	{
		SecurityCamera->ZoomAround(false);
		return;
	}

	if (HudWidgetComp) HudWidgetComp->ToggleCrosshair(false);

	if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(GetPawn()))
	{
		MyChar->FocusControl(false);
	}
}

void AHorrorPlayerController::Crouch_Start_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (ACharacter* MyChar = Cast<ACharacter>(OwnedPawn); MyChar && !MyChar->IsCrouched())
			MyChar->Crouch();
	}
}

void AHorrorPlayerController::Crouch_Stop_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (ACharacter* MyChar = Cast<ACharacter>(OwnedPawn); MyChar && MyChar->IsCrouched())
			MyChar->UnCrouch();
	}
}

void AHorrorPlayerController::Run_Start_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(OwnedPawn); MyChar && !MyChar->bIsRunning)
			MyChar->StartRun();
	}
}

void AHorrorPlayerController::Run_Stop_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(OwnedPawn); MyChar && MyChar->bIsRunning)
			MyChar->StopRun();
	}
}

void AHorrorPlayerController::Jump_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (ACharacter* MyChar = Cast<ACharacter>(OwnedPawn))
			MyChar->Jump();
	}
}

void AHorrorPlayerController::Interact_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(OwnedPawn))
			MyChar->FireInteraction();
	}
}

void AHorrorPlayerController::Restart_Action()
{
	if (LevelName.IsNone()) return;

	UGameplayStatics::OpenLevel(this, LevelName, true, FString());
}

void AHorrorPlayerController::Quit_Action()
{
	// HudWidgetComp->
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}

void AHorrorPlayerController::Flashlight_Action()
{
	if (APawn* OwnedPawn = GetPawn())
	{
		if (AHorrorBaseCharacter* MyChar = Cast<AHorrorBaseCharacter>(OwnedPawn))
			MyChar->ToggleSpotLight();
	}
}

void AHorrorPlayerController::ChangeView_Action()
{
}

void AHorrorPlayerController::Drone_Action()
{
}
