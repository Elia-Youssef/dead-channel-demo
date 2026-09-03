// Project By Rebel Art Studios.


#include "Frameworks/Players/FlashLightComponent.h"

#include "Components/SpotLightComponent.h"
#include "Engine/World.h"


// Disables frame ticking because the single battery timer performs all updates.
UFlashLightComponent::UFlashLightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Normalizes the configured charge and begins the state selected by the initial light setting.
void UFlashLightComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxBattery = FMath::Max(0.f, MaxBattery);
	CurrentBattery = FMath::Clamp(CurrentBattery, 0.f, MaxBattery);
	BatteryUpdateInterval = FMath::Max(BatteryUpdateInterval, 0.01f);
	ToggleLight(bOn);
}

// Changes the battery state, starts or stops the one timer, and updates spotlight visibility.
void UFlashLightComponent::ToggleLight(bool bEnable)
{
	bOn = bEnable && CurrentBattery > KINDA_SMALL_NUMBER;

	if (bOn)
	{
		BatteryState = EFlashLightBatteryState::Depleting;
	}
	else if (CurrentBattery >= MaxBattery)
	{
		BatteryState = EFlashLightBatteryState::Full;
	}
	else if (CurrentBattery <= KINDA_SMALL_NUMBER)
	{
		BatteryState = EFlashLightBatteryState::Empty;
	}
	else
	{
		BatteryState = EFlashLightBatteryState::Charging;
	}

	if (IsValid(SpotLightComponent))
	{
		SpotLightComponent->SetVisibility(bOn);
	}

	if (UWorld* World = GetWorld())
	{
		if (BatteryState == EFlashLightBatteryState::Full)
		{
			World->GetTimerManager().ClearTimer(BatteryTimerHandle);
		}
		else
		{
			World->GetTimerManager().SetTimer(
				BatteryTimerHandle,
				this,
				&UFlashLightComponent::UpdateBattery,
				BatteryUpdateInterval,
				true
			);
		}
	}

	OnBatteryChanged.Broadcast(CurrentBattery, MaxBattery);
	OnFlashLightStateChanged.Broadcast(bOn);
}

void UFlashLightComponent::ControlLight()
{
	if (!IsValid(SpotLightComponent)) return;

	SpotLightComponent->SetVisibility(bOn);
	SpotLightComponent->SetIntensityUnits(ELightUnits::Candelas);
	SpotLightComponent->SetCastShadows(bEnableShadows);
	SpotLightComponent->SetIntensity(LightIntensity);
	SpotLightComponent->SetInnerConeAngle(InnerCone);
	SpotLightComponent->SetInnerConeAngle(InnerCone);
	SpotLightComponent->SetOuterConeAngle(OuterCone);
	SpotLightComponent->SetAttenuationRadius(Attenuation);
	SpotLightComponent->SetUseTemperature(bUseTemperature);
	SpotLightComponent->SetTemperature(bUseTemperature ? LightTemperature : 6500);
	SpotLightComponent->SetLightColor(bUseTemperature ? FColor::White : LightColor);
}

// Selects exactly one battery action each time the shared repeating timer fires.
void UFlashLightComponent::UpdateBattery()
{
	switch (BatteryState)
	{
	case EFlashLightBatteryState::Depleting:
		DecreaseLight();
		break;

	case EFlashLightBatteryState::Charging:
		RechargeLight();
		break;

	case EFlashLightBatteryState::Empty:
		BatteryState = EFlashLightBatteryState::Charging;
		RechargeLight();
		break;

	case EFlashLightBatteryState::Full:
	default:
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(BatteryTimerHandle);
		}
		break;
	}
}

// Drains a time-scaled amount of charge and turns the spotlight off when it reaches empty.
void UFlashLightComponent::DecreaseLight()
{
	CurrentBattery = FMath::Clamp(
		CurrentBattery - FMath::Max(0.f, BatteryDepletionRate) * BatteryUpdateInterval,
		0.f,
		MaxBattery
	);

	if (CurrentBattery <= KINDA_SMALL_NUMBER)
	{
		CurrentBattery = 0.f;
		bOn = false;
		BatteryState = EFlashLightBatteryState::Empty;

		if (IsValid(SpotLightComponent))
		{
			SpotLightComponent->SetVisibility(false);
		}

		OnFlashLightStateChanged.Broadcast(false);
	}

	OnBatteryChanged.Broadcast(CurrentBattery, MaxBattery);
}

// Adds a time-scaled amount of charge and stops the shared timer once the battery is full.
void UFlashLightComponent::RechargeLight()
{
	CurrentBattery = FMath::Clamp(
		CurrentBattery + FMath::Max(0.f, BatteryRechargeRate) * BatteryUpdateInterval,
		0.f,
		MaxBattery
	);

	if (CurrentBattery >= MaxBattery)
	{
		CurrentBattery = MaxBattery;
		BatteryState = EFlashLightBatteryState::Full;

		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(BatteryTimerHandle);
		}
	}

	OnBatteryChanged.Broadcast(CurrentBattery, MaxBattery);
}
