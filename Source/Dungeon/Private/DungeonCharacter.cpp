#include "DungeonCharacter.h"

ADungeonCharacter::ADungeonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ADungeonCharacter::Damage(float value)
{
	Health = FMath::Clamp(Health - value, 0.0f, HealthMax);
}

void ADungeonCharacter::RestoreHealth(float value)
{
	Health = FMath::Clamp(Health + value, 0.0f, HealthMax);
}

void ADungeonCharacter::UseMana(float value)
{
	Mana = FMath::Clamp(Mana - value, 0.0f, ManaMax);
}

void ADungeonCharacter::RestoreMana(float value)
{
	Mana = FMath::Clamp(Mana + value, 0.0f, ManaMax);
}

void ADungeonCharacter::Fatigue(float value)
{
	Endurance = FMath::Clamp(Endurance - value, 0.0f, EnduranceMax);
}

void ADungeonCharacter::RestoreEndurance(float value)
{
	Endurance = FMath::Clamp(Endurance + value, 0.0f, EnduranceMax);
}

void ADungeonCharacter::Tick(float DeltaSeconds)
{
	ACharacter::Tick(DeltaSeconds);

	RestoreHealth(HealthReplenishRate * DeltaSeconds);
	RestoreMana(ManaReplenishRate * DeltaSeconds);
	RestoreEndurance(EnduranceReplenishRate * DeltaSeconds);
}
