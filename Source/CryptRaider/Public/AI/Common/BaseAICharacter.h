#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerOnSightDelegate, const bool, IsPlayerOnSight, const FVector&, PlayerLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FTakeStunDamage, AActor*, DamagedActor, float, Damage, const FHitResult&, Hit, class AController*, InstigatedBy, const UDamageType*, DamageType, AActor*, DamageCauser);

UCLASS()
class CRYPTRAIDER_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseAICharacter();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

	// If Duration is not set, animation duration will be used instead
	UFUNCTION(BlueprintCallable)
	void GetStunned(const float& Duration = 0.f);

	UFUNCTION()
	bool IsStunResistant();

protected:
	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	void PlayAttackAnimation();
	void AttackTrace();

	void StopAttack();
	void StopAttackTrace();

	void StartStun();
	void FinishStun();

	void SetSensesEnabled(bool IsEnabled);

public:
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY(BlueprintAssignable)
	FPlayerOnSightDelegate OnPlayerOnSightUpdate;

	UPROPERTY(BlueprintAssignable)
	FTakeStunDamage OnTakeStunDamage;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

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

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadOnly,
		Category = "AI|Stun",
		meta = (AllowPrivateAccess = "true")
	)
	bool bIsStunResistant = false;

	UPROPERTY(
		VisibleAnywhere, BlueprintReadOnly,
		Category = "AI|Stun",
		meta = (AllowPrivateAccess = "true")
	)
	bool bIsStunned;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Stun", DisplayName= "Animation montage",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UAnimMontage> StunAnimation;
	
	UPROPERTY()
	FTimerHandle StunTimerHandle;
};
