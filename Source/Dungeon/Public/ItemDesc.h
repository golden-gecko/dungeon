#pragma once

#include "CoreMinimal.h"
#include "ItemDesc.generated.h"

USTRUCT(BlueprintType)
struct FItemDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DisplayName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Attack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Defence;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Endurance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh;
};
