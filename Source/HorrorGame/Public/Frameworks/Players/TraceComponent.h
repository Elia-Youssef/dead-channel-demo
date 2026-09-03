// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "TraceComponent.generated.h"

class USceneComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORGAME_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTraceComponent();

	UFUNCTION(BlueprintCallable, Category = "Interaction|Trace")
	void SetTraceOrigin(USceneComponent* InTraceOrigin);

	UFUNCTION(BlueprintCallable, Category = "Interaction|Trace")
	void StartTracing();

	UFUNCTION(BlueprintCallable, Category = "Interaction|Trace")
	void StopTracing();

	UFUNCTION(BlueprintPure, Category = "Interaction|Trace")
	AActor* GetLastHitActor() const;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	AActor* TraceOnce();
	void RunTrace();

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace", meta = (ClampMin = "0.01"))
	float TraceInterval = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace", meta = (ClampMin = "0.0"))
	float TraceLength = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace")
	bool bDrawDebugTrace = true;

	TWeakObjectPtr<USceneComponent> TraceOrigin;
	TWeakObjectPtr<AActor> LastHitActor;
	FTimerHandle TraceTimerHandle;
};
