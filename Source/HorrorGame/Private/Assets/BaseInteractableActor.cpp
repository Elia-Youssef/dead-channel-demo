// Project By Rebel Art Studios.


#include "Assets/BaseInteractableActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"


// Constructor
ABaseInteractableActor::ABaseInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetMobility(EComponentMobility::Static);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComp"));
	ArrowComp->SetupAttachment(RootComponent);
	ArrowComp->SetMobility(EComponentMobility::Static);
	ArrowComp->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetMobility(EComponentMobility::Static);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	BoxComp->bHiddenInGame = true;
}

void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	if (BoxComp)
	{
		BoxComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseInteractableActor::OnBeginOverlap);
		BoxComp->OnComponentEndOverlap.AddUniqueDynamic(this, &ABaseInteractableActor::OnEndOverlap);
	}
}

void ABaseInteractableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                            bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UHorrorInterfaceInteract::StaticClass()))
	{
		IHorrorInterfaceInteract::Execute_StoreActor(OtherActor, this);
		IHorrorInterfaceInteract::Execute_ShowLabel(OtherActor, MyActorLabel);
	}
}

void ABaseInteractableActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UHorrorInterfaceInteract::StaticClass()))
	{
		IHorrorInterfaceInteract::Execute_StoreActor(OtherActor, nullptr);
		IHorrorInterfaceInteract::Execute_ShowLabel(OtherActor, FText::FromString(""));
	}
}

void ABaseInteractableActor::DoInteraction_Implementation()
{
	// Children Implement
}
