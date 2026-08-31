// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "HorrorInterfaceInteract.h"
#include "GameFramework/PlayerController.h"
#include "HorrorPlayerController.generated.h"


struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UFlashLightComponent;

UENUM()
enum class EFadeType : uint8
{
	FadeBlack,
	FadeClear,
	FadeIn,
	FadeOut
};


UCLASS()
class HORRORGAME_API AHorrorPlayerController : public APlayerController, public IHorrorInterfaceInteract
{
	GENERATED_BODY()

public:
	AHorrorPlayerController();

	UPROPERTY(EditDefaultsOnly, Category = "Level")
	FName LevelName = "";

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	void CameraFadeControl(EFadeType FadeType);

private:
	// Private Components
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<class UHudWidget> HudWidgetClass = nullptr;

	UPROPERTY()
	TObjectPtr<UHudWidget> HudWidgetComp = nullptr;

	UPROPERTY()
	TObjectPtr<UFlashLightComponent> BoundFlashLightComp = nullptr;


	// Enhanced Input Actions

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_HorrorGame = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Restart = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Quit = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Focus = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Crouch = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Run = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Interact = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_ChangeView = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Flashlight = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Drone = nullptr;

	// Enhanced Input Functions

	UFUNCTION()
	void Move_Action(const FInputActionValue& Value);

	UFUNCTION()
	void Look_Action(const FInputActionValue& Value);
	
	UFUNCTION()
	void Focus_Start_Action();
	
	UFUNCTION()
	void Focus_Stop_Action();

	UFUNCTION()
	void Crouch_Start_Action();

	UFUNCTION()
	void Crouch_Stop_Action();

	UFUNCTION()
	void Run_Start_Action();

	UFUNCTION()
	void Run_Stop_Action();

	UFUNCTION()
	void Jump_Action();

	UFUNCTION()
	void Interact_Action();

	UFUNCTION()
	void Restart_Action();

	UFUNCTION()
	void Quit_Action();

	UFUNCTION()
	void Flashlight_Action();

	UFUNCTION()
	void ChangeView_Action();

	UFUNCTION()
	void Drone_Action();

	void BindFlashLightComponent();

	UFUNCTION()
	void HandleFlashLightBatteryChanged(float CurrentBattery, float MaxBattery);

	UFUNCTION()
	void HandleFlashLightStateChanged(bool bIsOn);
};
