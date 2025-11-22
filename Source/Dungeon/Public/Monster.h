#pragma once

#include "CoreMinimal.h"
#include "DungeonCharacter.h"
#include "Monster.generated.h"

UCLASS(Blueprintable)
class AMonster : public ADungeonCharacter
{
	GENERATED_BODY()
	
public:
	AMonster();
};
