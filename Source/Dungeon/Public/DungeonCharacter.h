#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonCharacter.generated.h"

UCLASS(Blueprintable)
class ADungeonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HealthMax = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Mana = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ManaMax = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Endurance = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EnduranceMax = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HealthReplenishRate = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ManaReplenishRate = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EnduranceReplenishRate = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackRate = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DefenseRate = 10.0f;

public:
	ADungeonCharacter();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void Damage(float value);

	UFUNCTION(BlueprintCallable)
	void RestoreHealth(float value);

	UFUNCTION(BlueprintCallable)
	void UseMana(float value);

	UFUNCTION(BlueprintCallable)
	void RestoreMana(float value);

	UFUNCTION(BlueprintCallable)
	void Fatigue(float value);

	UFUNCTION(BlueprintCallable)
	void RestoreEndurance(float value);
};
