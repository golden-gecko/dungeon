#include "Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventory::StoreItem(FString id, int quantity)
{
	int* quantityInInventory = ItemQuantity.Find(id);

	if (quantityInInventory)
	{
		*quantityInInventory += quantity;
	}
	else
	{
		ItemQuantity.Add(id, quantity);
	}
}

void UInventory::RemoveItem(FString id, int quantity)
{
	int* quantityInInventory = ItemQuantity.Find(id);

	if (quantityInInventory)
	{
		*quantityInInventory -= quantity;
	}
}
