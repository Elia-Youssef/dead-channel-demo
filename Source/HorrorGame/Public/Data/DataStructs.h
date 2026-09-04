// Project By Rebel Art Studios.

#pragma once

#include "DataStructs.generated.h"

// Level Structs
USTRUCT(BlueprintType)
struct FLevelData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName = FName("LevelName");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonName = FText::FromString("ButtonName");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath LevelPath;
};
