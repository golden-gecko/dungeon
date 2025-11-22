#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

UCLASS(Blueprintable)
class DUNGEON_API ADungeonGenerator : public AActor
{
    GENERATED_BODY()

public:
    // Maze parameters.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    double TileSize = 250.0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 MazeSize = 16;

    // Tiles.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UClass>> TileDoors;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UClass> TileEmpty;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UClass> TileFull;

    // Items.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UClass>> Chests;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UClass>> Doors;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UDataTable> Potions;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UClass>> Traps;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UDataTable> Weapons;

    // Monsters.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UClass>> Monsters;

    // Others.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UClass> ItemTemplate;

public:
    ADungeonGenerator();

protected:
    virtual void BeginPlay() override;

private:
    // Generate dungeon.
    void Generate(unsigned int seed);

    // Generate tiles.
    void GenerateTileDoor(int x, int y, const FRotator& rotator);
    void GenerateTileEmpty(int x, int y);
    void GenerateTileFull(int x, int y);

    // Generate items.
    /*
    void GenerateChest(int x, int y);
    void GenerateMonster(int x, int y);
    void GeneratePotion(int x, int y);
    void GenerateTrap(int x, int y, const FRotator& rotator);
    */
    void GenerateItem(UDataTable* items, int x, int y);

    // Spawn actors.
    void Spawn(TObjectPtr<UClass> class_, const FVector& location, const FRotator& rotator = FRotator::ZeroRotator);
    void SpawnCharacter(TObjectPtr<UClass> class_, const FVector& location, const FRotator& rotator = FRotator::ZeroRotator);

    // Utils.
    FVector GetLocation(int x, int y);
    TObjectPtr<UClass> GetRandomClass(const TArray<TObjectPtr<UClass>>& classes);
};
