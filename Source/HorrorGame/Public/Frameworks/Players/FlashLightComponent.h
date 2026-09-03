// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "FlashLightComponent.generated.h"

// Forward Declarations
class USpotLightComponent;


// Represents the active phase of the flashlight battery.
UENUM(BlueprintType)
enum class EFlashLightBatteryState : uint8
{
	Empty, Charging, Full, Depleting
};

// Reports battery quantities to listeners such as the HUD.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFlashLightBatteryChanged, float, CurrentBattery, float, MaxBattery);

// Reports whether the flashlight is currently emitting light.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlashLightStateChanged, bool, bIsOn);

// Main Class
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORGAME_API UFlashLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Creates a timer-driven component without a per-frame tick.
	UFlashLightComponent();

	// Initializes the battery and starts the correct state-driven timer behavior.
	virtual void BeginPlay() override;

	// Component Pointer
	UPROPERTY()
	TObjectPtr<USpotLightComponent> SpotLightComponent = nullptr;

	// Variables
	UPROPERTY(EditAnywhere, Category = "Light")
	bool bOn = false;
	UPROPERTY(EditAnywhere, Category = "Light")
	bool bEnableShadows = false;
	UPROPERTY(EditAnywhere, Category = "Light")
	bool bUseTemperature = false;

	UPROPERTY(EditAnywhere, Category = "Light")
	float LightIntensity = 10.f;
	UPROPERTY(EditAnywhere, Category = "Light")
	FColor LightColor = FColor::White;
	UPROPERTY(EditAnywhere, Category = "Light")
	float LightTemperature = 4500.f;
	UPROPERTY(EditAnywhere, Category = "Light")
	float InnerCone = 0.f;
	UPROPERTY(EditAnywhere, Category = "Light")
	float OuterCone = 50.f;
	UPROPERTY(EditAnywhere, Category = "Light")
	float Attenuation = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Battery")
	float MaxBattery = 100.f;
	UPROPERTY(EditAnywhere, Category = "Battery")
	float CurrentBattery = 100.f;
	UPROPERTY(EditAnywhere, Category = "Battery")
	float BatteryDepletionRate = 10.f;
	UPROPERTY(EditAnywhere, Category = "Battery")
	float BatteryRechargeRate = 10.f;

	// Controls how often the single battery timer updates its current state.
	UPROPERTY(EditAnywhere, Category = "Battery", meta = (ClampMin = "0.01"))
	float BatteryUpdateInterval = 0.1f;

	// Exposes the current state for UI and Blueprint inspection.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battery")
	EFlashLightBatteryState BatteryState = EFlashLightBatteryState::Full;

	// Broadcasts every time the amount of stored charge changes.
	UPROPERTY(BlueprintAssignable, Category = "Battery")
	FOnFlashLightBatteryChanged OnBatteryChanged;

	// Broadcasts every time the physical flashlight turns on or off.
	UPROPERTY(BlueprintAssignable, Category = "Battery")
	FOnFlashLightStateChanged OnFlashLightStateChanged;

	// Helpers
	// Starts depletion or charging and keeps the visual light synchronized with bOn.
	UFUNCTION()
	void ToggleLight(bool bEnable);
	UFUNCTION()
	void ControlLight();
	// Removes charge for one timer interval while the state is Depleting.
	UFUNCTION()
	void DecreaseLight();
	// Restores charge for one timer interval while the state is Charging.
	UFUNCTION()
	void RechargeLight();

private:
	// Drives the single timer by running the behavior for the current battery state.
	UFUNCTION()
	void UpdateBattery();

	// Stores the one timer used for both depletion and charging.
	FTimerHandle BatteryTimerHandle;
};
