#include "DungeonGenerator.h"
#include "GameFramework/Character.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h" 
#include "mazegen.hpp"
#include "Monster.h"
#include "NavigationSystem.h"

namespace
{
    bool IsDoor(int region)
    {
        return mazegen::is_door(region);
    }

    bool IsWall(int region)
    {
        return region == mazegen::NOTHING_ID;
    }

    bool IsEmpty(int region)
    {
        return IsDoor(region) == false && IsWall(region) == false;
    }
}

ADungeonGenerator::ADungeonGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADungeonGenerator::BeginPlay()
{
    Super::BeginPlay();

    Generate(1);
}

void ADungeonGenerator::Generate(unsigned int seed)
{
    mazegen::Config cfg;

    cfg.ROOM_BASE_NUMBER = 25;
    cfg.ROOM_SIZE_MIN = 1;
    cfg.ROOM_SIZE_MAX = 2;
    cfg.EXTRA_CONNECTION_CHANCE = 0.0;
    cfg.WIGGLE_CHANCE = 0.5;
    cfg.DEADEND_CHANCE = 0.5;
    cfg.RECONNECT_DEADENDS_CHANCE = 0.5;
    cfg.CONSTRAIN_HALL_ONLY = true;

    mazegen::Generator generator;

    generator.set_seed(seed);
    generator.generate(MazeSize, MazeSize, cfg);

    bool playerStartSet = false;

    for (int x = 0; x < generator.grid.size(); x++)
    {
        for (int y = 0; y < generator.grid[x].size(); y++)
        {
            int region = generator.region_at(x, y);

            int regionTop = generator.region_at(x, y + 1);
            int regionBottom = generator.region_at(x, y - 1);

            int regionLeft = generator.region_at(x - 1, y);
            int regionRight = generator.region_at(x + 1, y);

            FRotator rotator = IsWall(regionTop) ? FRotator(0.0, 90.0, 0.0) : FRotator::ZeroRotator;

            if (IsWall(region))
            {
                GenerateTileFull(x, y);
            }
            else if (IsDoor(region))
            {
                GenerateTileDoor(x, y, rotator);
            }
            else if (IsEmpty(region))
            {
                GenerateTileEmpty(x, y);

                // Set player location to first empty tile.
                if (playerStartSet == false)
                {
                    UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(GetLocation(x, y));

                    playerStartSet = true;
                }
                // Add random items or traps to empty tiles.
                else
                {
                    // GenerateItem(Weapons, x, y);

                    /*
                    switch (FMath::RandRange(0, 4))
                    {
                        case 0: GenerateChest(x, y); break;
                        case 1: GenerateMonster(x, y); break;
                        case 2: GenerateItem(Potions, x, y); break;
                        case 3: GenerateTrap(x, y, rotator); break;
                        case 4: GenerateItem(Weapons, x, y); break;
                    }
                    */
                }
            }
        }
    }
}

void ADungeonGenerator::GenerateTileDoor(int x, int y, const FRotator& rotator)
{
    Spawn(GetRandomClass(TileDoors), GetLocation(x, y), rotator);
    Spawn(GetRandomClass(Doors), GetLocation(x, y), rotator);
}

void ADungeonGenerator::GenerateTileEmpty(int x, int y)
{
    Spawn(TileEmpty, GetLocation(x, y));
}

void ADungeonGenerator::GenerateTileFull(int x, int y)
{
    Spawn(TileFull, GetLocation(x, y));
}

/*
void ADungeonGenerator::GenerateChest(int x, int y)
{
    Spawn(GetRandomClass(Chests), GetLocation(x, y));
}

void ADungeonGenerator::GenerateMonster(int x, int y)
{
    SpawnCharacter(GetRandomClass(Monsters), GetLocation(x, y));
}

void ADungeonGenerator::GeneratePotion(int x, int y)
{
    Spawn(GetRandomClass(Potions), GetLocation(x, y) + FVector(0.0, 0.0, 10.0));
}

void ADungeonGenerator::GenerateTrap(int x, int y, const FRotator& rotator)
{
    Spawn(GetRandomClass(Traps), GetLocation(x, y), rotator);
}
*/

void ADungeonGenerator::GenerateItem(UDataTable* items, int x, int y)
{
    if (ItemTemplate == nullptr || items == nullptr)
    {
        return;
    }

    TArray<FName> names = items->GetRowNames();

    if (names.Num() <= 0)
    {
        return;
    }

    AItem* item = GetWorld()->SpawnActor<AItem>(ItemTemplate, GetLocation(x, y) + FVector(0.0, 0.0, 10.0), FRotator::ZeroRotator);

    if (item == nullptr)
    {
        return;
    }

    FItemDesc* itemDesc = items->FindRow<FItemDesc>(names[FMath::RandRange(0, names.Num() - 1)], "");

    if (itemDesc == nullptr)
    {
        return;
    }

    item->ItemDesc = *(itemDesc);
    item->ItemMesh->SetStaticMesh(item->ItemDesc.Mesh);
}

void ADungeonGenerator::Spawn(TObjectPtr<UClass> class_, const FVector& location, const FRotator& rotator)
{
    GetWorld()->SpawnActor<AActor>(class_, location, rotator);
}

void ADungeonGenerator::SpawnCharacter(TObjectPtr<UClass> class_, const FVector& location, const FRotator& rotator)
{
    ACharacter* character = GetWorld()->SpawnActor<ACharacter>(class_, location, rotator);

    if (character)
    {
        character->SpawnDefaultController();
    }
}

FVector ADungeonGenerator::GetLocation(int x, int y)
{
    return FVector(TileSize + x * TileSize * 2.0, TileSize + y * TileSize * 2.0, 0.0);
}

TObjectPtr<UClass> ADungeonGenerator::GetRandomClass(const TArray<TObjectPtr<UClass>>& classes)
{
    if (classes.Num() <= 0)
    {
        return nullptr;
    }

    return classes[FMath::RandRange(0, classes.Num() - 1)];
}
