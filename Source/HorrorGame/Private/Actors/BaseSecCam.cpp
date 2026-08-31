// Project By Rebel Art Studios.


#include "Actors/BaseSecCam.h"

#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Controller.h"

ABaseSecCam::ABaseSecCam()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;
	SceneRoot->SetMobility(EComponentMobility::Movable);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SceneRoot);
	CameraComp->bUsePawnControlRotation = true;

	PostProcessorComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessor"));
	PostProcessorComp->SetupAttachment(CameraComp);
	PostProcessorComp->bUnbound = false;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ABaseSecCam::BeginPlay()
{
	Super::BeginPlay();

	CameraComp->SetFieldOfView(DefaultFieldOfView);
}

void ABaseSecCam::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeControlRotation(NewController);
}

void ABaseSecCam::PanAround(const FVector2D& LookValue)
{
	if (LookValue.IsNearlyZero() || !IsValid(Controller))
	{
		return;
	}

	const FRotator CurrentControlRotation = Controller->GetControlRotation();
	const float DesiredYawOffset = FMath::FindDeltaAngleDegrees(
		HomeControlRotation.Yaw,
		CurrentControlRotation.Yaw + LookValue.X * PanSpeed);
	const float DesiredPitchOffset = FMath::FindDeltaAngleDegrees(
		HomeControlRotation.Pitch,
		CurrentControlRotation.Pitch + LookValue.Y * PanSpeed);

	FRotator NewControlRotation = HomeControlRotation;
	NewControlRotation.Yaw += FMath::Clamp(DesiredYawOffset, -MaxYawOffset, MaxYawOffset);
	NewControlRotation.Pitch += FMath::Clamp(DesiredPitchOffset, MinPitchOffset, MaxPitchOffset);
	NewControlRotation.Roll = 0.0f;

	Controller->SetControlRotation(NewControlRotation);
}

void ABaseSecCam::ZoomAround(bool bZoomIn)
{
	if (!IsValid(CameraComp))
	{
		return;
	}

	CameraComp->SetFieldOfView(bZoomIn ? ZoomedFieldOfView : DefaultFieldOfView);
}

void ABaseSecCam::InitializeControlRotation(AController* NewController)
{
	if (!IsValid(NewController))
	{
		return;
	}

	HomeControlRotation = GetActorRotation();
	HomeControlRotation.Roll = 0.0f;
	NewController->SetControlRotation(HomeControlRotation);
}

