// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Frameworks/Interfaces/HorrorInterfaceInteract.h"
#include "GameFramework/Character.h"
#include "HorrorBaseCharacter.generated.h"


class UPlayerCamComponent;
class UTraceComponent;
// Forward Declarations
class UCameraComponent;
class USpringArmComponent;
class UFlashLightComponent;
class USpotLightComponent;

// Player Views
UENUM()
enum class EPlayerViewType : uint8
{
	FirstPerson,
	ThirdPerson
};


UCLASS()
class HORRORGAME_API AHorrorBaseCharacter : public ACharacter, public IHorrorInterfaceInteract
{
	GENERATED_BODY()

public:
	// Public Native Functions
	AHorrorBaseCharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

	// Movement Control Function
	void HandleMove(const FVector2D MoveValue);
	void HandleLook(const FVector2D LookValue);
	void StartRun();
	void StopRun();

	//
	UFUNCTION()
	void FireInteraction();
	
	UPROPERTY()
	bool bIsRunning = false;

	// View Control
	void SwapPlayerView(EPlayerViewType PlayerView);

	void FadeControl();
	void FocusControl(bool bFocus);

	// Light
	void ToggleSpotLight();
	UFlashLightComponent* GetFlashLightComponent() const { return FlashLightComp.Get(); }

protected:
	// Interface Functions

	UFUNCTION()
	virtual void CallCharacter_FireInteraction_Implementation() override;

	UFUNCTION()
	virtual void StoreActor_Implementation(AActor* StoredActor) override;

private:
	// Private Components

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> TPCamComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> FPCamComp = nullptr;

	UPROPERTY()
	AActor* CurrentStoredActor = nullptr;

	EPlayerViewType CurrentPlayerView = EPlayerViewType::ThirdPerson;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpotLightComponent> SpotLightComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UFlashLightComponent> FlashLightComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UTraceComponent> TraceComp = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UPlayerCamComponent> PlayerCamComp = nullptr;

	// Movement Variables

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WalkingSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RunningSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float LookingSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float DefaultFov = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float FocusFov = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float FocusDuration = 0.25f;

	// Runtime state for the current FOV transition
	float FocusStartFov = 0.f;
	float FocusTargetFov = 0.f;
	float FocusStartTime = 0.f;

	// Helper Functions
	void UpdateTraceOrigin();

	void FocusTimer();
	FTimerHandle FocusTimerHandle;

	void CameraSwitchTimer();
	FTimerHandle CameraSwitchTimerHandle;
};
