// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ClassicAICharacter.generated.h"

UCLASS()
class CRYPTRAIDER_API AClassicAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClassicAICharacter();

protected:
	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

private:
	void PlayAttackAnimation();
	void AttackTrace();

	void StopAttack();
	void StopAttackTrace();

private:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FName IsPlayerOnSightName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FName IsPursuingPlayerName;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName="Damage",
		meta = (AllowPrivateAccess = "true")
	)
	float AttackDamage = 0.f;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName="Start Hit Socket",
		meta = (AllowPrivateAccess = "true")
	)
	FName AttackStartSocketName;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName="End Hit Socket",
		meta = (AllowPrivateAccess = "true")
	)
	FName AttackEndSocketName;

	// Rate of attack line trace, in seconds
	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName= "Trace Rate",
		meta = (AllowPrivateAccess = "true")
	)
	float AttackTraceRate = 0.01f;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName= "Animation montage",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY()
	FTimerHandle AttackTraceTimerHandle;

	UPROPERTY()
	FTimerHandle AttackAnimationTimerHandle;
};
