// Project By Rebel Art Studios.

#pragma once

#include "DataStructs.generated.h"

// Level Structs
USTRUCT(BlueprintType)
struct FLevelData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName = FName("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath LevelPath;
};
