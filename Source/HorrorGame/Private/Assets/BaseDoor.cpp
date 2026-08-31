// Project By Rebel Art Studios.


#include "Assets/BaseDoor.h"


ABaseDoor::ABaseDoor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

