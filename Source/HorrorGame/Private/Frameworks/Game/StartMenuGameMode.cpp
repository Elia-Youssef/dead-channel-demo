// Project By Rebel Art Studios.


#include "Frameworks/Game/StartMenuGameMode.h"
#include "Frameworks/Controllers/StartMenuPlayerController.h"
#include "Kismet/GameplayStatics.h"


void AStartMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AStartMenuPlayerController* PC = Cast<AStartMenuPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->OnLevelSwitchRequested.BindUObject(this, &AStartMenuGameMode::SwitchLevels);
	}
}

void AStartMenuGameMode::SwitchLevels(FName LevelName)
{
	if (LevelName.IsNone()) return;
	UGameplayStatics::OpenLevel(this, LevelName, true);
}
