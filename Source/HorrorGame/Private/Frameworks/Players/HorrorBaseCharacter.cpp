// Project By Rebel Art Studios.

#include "HorrorGame/Public/Frameworks/Players/HorrorBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "Engine/World.h"
#include "Frameworks/Players/FlashLightComponent.h"
#include "Frameworks/Controllers/HorrorPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerManager.h"
#include "Frameworks/Players/PlayerCamComponent.h"
#include "Frameworks/Players/TraceComponent.h"


AHorrorBaseCharacter::AHorrorBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	GetCharacterMovement()->MovementState.bCanCrouch = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	bUseControllerRotationYaw = false;
	bIsRunning = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.f;
	SpringArmComp->bEnableCameraRotationLag = true;
	SpringArmComp->CameraRotationLagSpeed = 5.f;

	TPCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	TPCamComp->SetupAttachment(SpringArmComp, GetAttachParentSocketName());
	TPCamComp->bUsePawnControlRotation = false;

	FPCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamComp->SetupAttachment(GetCapsuleComponent());
	FPCamComp->bUsePawnControlRotation = true;

	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComp->SetupAttachment(FPCamComp);
	SpotLightComp->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	SpotLightComp->SetIntensityUnits(ELightUnits::Candelas);

	FlashLightComp = CreateDefaultSubobject<UFlashLightComponent>(TEXT("FlashLight"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComponent"));
	PlayerCamComp = CreateDefaultSubobject<UPlayerCamComponent>(TEXT("PlayerCamComp"));
}

void AHorrorBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Defaults
	TPCamComp->SetFieldOfView(DefaultFov);
	FPCamComp->SetFieldOfView(DefaultFov);

	// Both camera components are auto-activated by default. Make the configured
	// starting view explicit so focus always changes the camera used by the viewport.
	SwapPlayerView(CurrentPlayerView);

	// Light Components
	if (FlashLightComp && SpotLightComp)
	{
		if (!IsValid(FlashLightComp->SpotLightComponent)) FlashLightComp->SpotLightComponent = SpotLightComp;

		FlashLightComp->ToggleLight(false);
	}
}

// Called to bind functionality to input
void AHorrorBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHorrorBaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (FlashLightComp)
	{
		if (!IsValid(FlashLightComp->SpotLightComponent))
			FlashLightComp->SpotLightComponent = SpotLightComp;

		FlashLightComp->ControlLight();
	}
}

void AHorrorBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStoredActor)
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("Stored"));
}

void AHorrorBaseCharacter::HandleMove(const FVector2D MoveValue)
{
	if (MoveValue.IsNearlyZero()) return;

	const FRotator ConRot = Controller->GetControlRotation();
	const FRotator LocalRotation = FRotator(0.f, ConRot.Yaw, 0.f);
	const FVector ForwardVec = FRotationMatrix(LocalRotation).GetUnitAxis(EAxis::X);
	const FVector RightVec = FRotationMatrix(LocalRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVec, MoveValue.Y);
	AddMovementInput(RightVec, MoveValue.X);
	//
	// AddMovementInput(GetActorForwardVector(), MoveValue.Y);
	// AddMovementInput(GetActorRightVector(), MoveValue.X);
}

void AHorrorBaseCharacter::HandleLook(const FVector2D LookValue)
{
	if (LookValue.IsNearlyZero()) return;

	AddControllerYawInput(LookValue.X * LookingSpeed);
	AddControllerPitchInput(LookValue.Y * LookingSpeed);
}

void AHorrorBaseCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	bIsRunning = true;
}

void AHorrorBaseCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	bIsRunning = false;
}

void AHorrorBaseCharacter::SwapPlayerView(EPlayerViewType PlayerView)
{
	switch (PlayerView)
	{
	case EPlayerViewType::FirstPerson:
	default:
		CurrentPlayerView = EPlayerViewType::FirstPerson;
		FPCamComp->SetActive(true);
		TPCamComp->SetActive(false);
		GetMesh()->SetVisibility(false);
		FPCamComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
		bUseControllerRotationYaw = true;
		break;

	case EPlayerViewType::ThirdPerson:
		CurrentPlayerView = EPlayerViewType::ThirdPerson;
		FPCamComp->SetActive(false);
		TPCamComp->SetActive(true);
		GetMesh()->SetVisibility(true);
		FPCamComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
		bUseControllerRotationYaw = false;
		break;
	}

	UpdateTraceOrigin();
}

void AHorrorBaseCharacter::FadeControl()
{
	if (AHorrorPlayerController* PC = Cast<AHorrorPlayerController>(GetController()))
	{
		// PC->CameraFadeControl
	}
}

void AHorrorBaseCharacter::FocusControl(bool bFocus)
{
	GetCharacterMovement()->bOrientRotationToMovement = !bFocus;
	bUseControllerRotationYaw = bFocus;

	UCameraComponent* CurrentCam = CurrentPlayerView == EPlayerViewType::FirstPerson
		                               ? FPCamComp.Get()
		                               : TPCamComp.Get();
	UWorld* World = GetWorld();

	if (!CurrentCam || !World) return;

	// Begin at the camera's actual current FOV, allowing smooth reversal mid-transition.
	FocusStartFov = CurrentCam->FieldOfView;
	FocusTargetFov = bFocus ? FocusFov : DefaultFov;
	FocusStartTime = World->GetTimeSeconds();

	if (FMath::IsNearlyEqual(FocusStartFov, FocusTargetFov) || FocusDuration <= KINDA_SMALL_NUMBER)
	{
		CurrentCam->SetFieldOfView(FocusTargetFov);
		World->GetTimerManager().ClearTimer(FocusTimerHandle);
		return;
	}

	World->GetTimerManager().SetTimer(FocusTimerHandle, this, &AHorrorBaseCharacter::FocusTimer,
	                                  0.01f, true);
}

void AHorrorBaseCharacter::ToggleSpotLight()
{
	if (!IsValid(FlashLightComp)) return;

	FlashLightComp->ToggleLight(!FlashLightComp->bOn);
}

void AHorrorBaseCharacter::CallCharacter_FireInteraction_Implementation()
{
	// IHorrorInterfaceInteract::CallCharacter_FireInteraction_Implementation();

	FireInteraction();
}


void AHorrorBaseCharacter::StoreActor_Implementation(AActor* StoredActor)
{
	// IHorrorInterfaceInteract::StoreActor_Implementation(MyInstigator);
	CurrentStoredActor = StoredActor;

	if (!IsValid(TraceComp)) return;

	if (IsValid(CurrentStoredActor)) TraceComp->StartTracing();
	else TraceComp->StopTracing();
}

void AHorrorBaseCharacter::FireInteraction()
{
	if (!IsValid(CurrentStoredActor)) return;
	IHorrorInterfaceInteract::Execute_DoInteraction(CurrentStoredActor);
}

void AHorrorBaseCharacter::UpdateTraceOrigin()
{
	if (!IsValid(TraceComp)) return;

	UCameraComponent* CurrentCam = CurrentPlayerView == EPlayerViewType::FirstPerson
		                               ? FPCamComp.Get()
		                               : TPCamComp.Get();
	TraceComp->SetTraceOrigin(CurrentCam);
}

void AHorrorBaseCharacter::FocusTimer()
{
	UCameraComponent* CurrentCam = CurrentPlayerView == EPlayerViewType::FirstPerson
		                               ? FPCamComp.Get()
		                               : TPCamComp.Get();

	if (!CurrentCam || !GetWorld())
	{
		if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(FocusTimerHandle);
		return;
	}

	const float Elapsed = GetWorld()->GetTimeSeconds() - FocusStartTime;
	const float Alpha = FMath::Clamp(Elapsed / FocusDuration, 0.f, 1.f);

	CurrentCam->SetFieldOfView(FMath::Lerp(FocusStartFov, FocusTargetFov, Alpha));

	if (Alpha >= 1.f) GetWorld()->GetTimerManager().ClearTimer(FocusTimerHandle);
}

void AHorrorBaseCharacter::CameraSwitchTimer()
{
}
