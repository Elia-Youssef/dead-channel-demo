// Project By Rebel Art Studios.

#include "Frameworks/TraceComponent.h"

#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UTraceComponent::SetTraceOrigin(USceneComponent* InTraceOrigin)
{
	TraceOrigin = InTraceOrigin;

	UWorld* World = GetWorld();
	if (IsValid(World) && World->GetTimerManager().IsTimerActive(TraceTimerHandle))
	{
		RunTrace();
	}
}

void UTraceComponent::StartTracing()
{
	if (!IsValid(GetWorld()) || !IsValid(TraceOrigin.Get()) ||
		GetWorld()->GetTimerManager().IsTimerActive(TraceTimerHandle))
	{
		return;
	}

	RunTrace();
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &UTraceComponent::RunTrace,
	                                       TraceInterval, true);
}

void UTraceComponent::StopTracing()
{
	LastHitActor.Reset();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TraceTimerHandle);
	}
}

AActor* UTraceComponent::GetLastHitActor() const
{
	return LastHitActor.Get();
}

void UTraceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopTracing();
	Super::EndPlay(EndPlayReason);
}

AActor* UTraceComponent::TraceOnce()
{
	UWorld* World = GetWorld();
	USceneComponent* Origin = TraceOrigin.Get();
	AActor* Owner = GetOwner();
	if (!IsValid(World) || !IsValid(Origin) || !IsValid(Owner))
	{
		LastHitActor.Reset();
		return nullptr;
	}

	const FVector StartLocation = Origin->GetComponentLocation();
	const FVector EndLocation = StartLocation + Origin->GetForwardVector() * TraceLength;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);

	const bool bHit = World->LineTraceSingleByChannel(
		HitResult, StartLocation, EndLocation, TraceChannel, QueryParams);

	if (bDrawDebugTrace)
	{
		DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, TraceInterval);
	}

	LastHitActor = bHit ? HitResult.GetActor() : nullptr;
	return LastHitActor.Get();
}

void UTraceComponent::RunTrace()
{
	TraceOnce();
}
