// Project By Rebel Art Studios.


#include "Tools/CircularArray.h"

#include "Components/ArrowComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"


ACircularArray::ACircularArray()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Static);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(RootComponent);
	ArrowComp->SetMobility(EComponentMobility::Static);
	ArrowComp->AddRelativeRotation(FRotator(90.f, 0.f, 0.f));

	Ism_Comp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Ism"));
	Ism_Comp->SetupAttachment(RootComponent);
	Ism_Comp->SetMobility(EComponentMobility::Static);
}

void ACircularArray::BeginPlay()
{
	Super::BeginPlay();
}


void ACircularArray::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateShape();
}

void ACircularArray::UpdateShape()
{
	if (!IsValid(Ism_Comp)) return;

	Ism_Comp->SetStaticMesh(SourceMesh);
	Ism_Comp->ClearInstances();

	if (!IsValid(SourceMesh) || Num <= 0) return;

	const float AngleStep = 360.0f / static_cast<float>(Num);
	const FVector RadiusVector(Radius, 0.0f, 0.0f);
	const FVector HeightOffset(0.0f, 0.0f, Height);

	for (int32 Index = 0; Index < Num; ++Index)
	{
		const float Angle = AngleStep * static_cast<float>(Index);
		const FVector CircleLocation = RadiusVector.RotateAngleAxis(Angle, FVector::UpVector);
		const FVector Location = CircleLocation + HeightOffset;

		Ism_Comp->AddInstance(FTransform(Rot, Location));
	}
}
