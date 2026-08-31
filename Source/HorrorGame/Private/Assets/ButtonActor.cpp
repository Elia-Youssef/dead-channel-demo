// Project By Rebel Art Studios.


#include "Assets/ButtonActor.h"
#include "Components/WidgetComponent.h"
#include "UMG/ButtonWidget.h"


AButtonActor::AButtonActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("BaseMesh"));
	BaseMeshComp->SetupAttachment(RootComponent);
	BaseMeshComp->SetMobility(EComponentMobility::Static);

	TopMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("TopMesh"));
	TopMeshComp->SetupAttachment(RootComponent);
	TopMeshComp->SetMobility(EComponentMobility::Static);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComponent"));
	WidgetComp->SetupAttachment(BaseMeshComp);
	WidgetComp->SetMobility(EComponentMobility::Static);
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AButtonActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AssignMaterial();
	UpdateEmissiveProp();
	SetWidgetText();
}

void AButtonActor::ButtonPressed(bool bPressed)
{
}

void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	AssignMaterial();
	UpdateEmissiveProp();
	SetWidgetText();
	ToggleWidget(false);
}

void AButtonActor::DoInteraction_Implementation()
{
	Super::DoInteraction_Implementation();

	if (CalledActors.IsEmpty()) return;

	for (AActor* MyActor : CalledActors)
	{
		if (IsValid(MyActor) && MyActor->GetClass()->ImplementsInterface(UHorrorInterfaceInteract::StaticClass()))
		{
			IHorrorInterfaceInteract::Execute_CallReceivingActor(MyActor);
		}
	}
}

void AButtonActor::AssignMaterial()
{
	if (!IsValid(TopMeshComp)) return;

	for (const TPair<int32, UMaterialInterface*>& EmissiveMaterial : EmissiveProp.EmissiveMat)
	{
		if (IsValid(EmissiveMaterial.Value))
		{
			TopMeshComp->SetMaterial(EmissiveMaterial.Key, EmissiveMaterial.Value);
			TopMeshComp->SetCustomPrimitiveDataFloat(0, EmissiveProp.EmissiveIntensity);
			const FLinearColor& Color = EmissiveProp.EmissiveColor;
			const FVector4 NewColor = FVector4(Color.R, Color.G, Color.B, Color.A);
			TopMeshComp->SetCustomPrimitiveDataVector4(1, NewColor);
		}
	}
}

void AButtonActor::UpdateEmissiveProp()
{
}

void AButtonActor::SetWidgetText()
{
	if (!IsValid(WidgetComp) || !ButtonWidgetClass) return;

	WidgetComp->SetWidgetClass(ButtonWidgetClass);

	if (UButtonWidget* ButtonWidget = Cast<UButtonWidget>(WidgetComp->GetUserWidgetObject()))
		ButtonWidget->SetLabelText(MyActorLabel);
}

void AButtonActor::ToggleWidget(bool bEnable)
{
	if (!IsValid(WidgetComp) || !ButtonWidgetClass) return;
	WidgetComp->SetVisibility(bEnable);
}
