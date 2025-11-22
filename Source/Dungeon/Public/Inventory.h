#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "Inventory.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEON_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, int> ItemQuantity;

public:
	UInventory();

	UFUNCTION(BlueprintCallable)
	void StoreItem(FString id, int quantity);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(FString id, int quantity);

private:
	TMap<FString, TObjectPtr<AItem>> ItemActor;
};
