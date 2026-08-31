// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircularArray.generated.h"

class UArrowComponent;
class UInstancedStaticMeshComponent;
class UStaticMesh;

UCLASS()
class HORRORGAME_API ACircularArray : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACircularArray();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UArrowComponent> ArrowComp = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Circular Array")
	TObjectPtr<UStaticMesh> SourceMesh;

	UPROPERTY(VisibleAnywhere, Category = "Circular Array")
	TObjectPtr<UInstancedStaticMeshComponent> Ism_Comp = nullptr;

	// Variables
	UPROPERTY(EditAnywhere, Category = "Circular Array", meta = (ClampMin = "1", UIMin = "1"))
	int32 Num = 1;

	UPROPERTY(EditAnywhere, Category = "Circular Array", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Circular Array")
	float Height = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Circular Array")
	FRotator Rot = FRotator::ZeroRotator;
	
	void UpdateShape();
};
