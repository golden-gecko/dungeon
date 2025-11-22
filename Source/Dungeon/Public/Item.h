#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDesc.h"
#include "Item.generated.h"

UCLASS()
class DUNGEON_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Storable = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FItemDesc ItemDesc;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* ItemMesh;

public:	
	AItem();
};
