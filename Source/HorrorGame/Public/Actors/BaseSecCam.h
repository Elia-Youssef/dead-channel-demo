// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseSecCam.generated.h"

class UCameraComponent;
class UPostProcessComponent;
class USceneComponent;
class AController;

UCLASS()
class HORRORGAME_API ABaseSecCam : public APawn
{
	GENERATED_BODY()

public:
	ABaseSecCam();
	virtual void BeginPlay() override;

	// Called by the player controller while this pawn is possessed.
	UFUNCTION(BlueprintCallable, Category = "Security Camera")
	void PanAround(const FVector2D& LookValue);

	UFUNCTION(BlueprintCallable, Category = "Security Camera")
	void ZoomAround(bool bZoomIn);

protected:
	virtual void PossessedBy(AController* NewController) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComp = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPostProcessComponent> PostProcessorComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Security Camera|Pan", meta = (ClampMin = "0.0"))
	float PanSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Security Camera|Pan", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float MaxYawOffset = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Security Camera|Pan", meta = (ClampMin = "-89.0", ClampMax = "89.0"))
	float MinPitchOffset = -45.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Security Camera|Pan", meta = (ClampMin = "-89.0", ClampMax = "89.0"))
	float MaxPitchOffset = 45.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Security Camera|Zoom", meta = (ClampMin = "5.0", ClampMax = "170.0"))
	float DefaultFieldOfView = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Security Camera|Zoom", meta = (ClampMin = "5.0", ClampMax = "170.0"))
	float ZoomedFieldOfView = 45.0f;

	FRotator HomeControlRotation = FRotator::ZeroRotator;

	void InitializeControlRotation(AController* NewController);

};
