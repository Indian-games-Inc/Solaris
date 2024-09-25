#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
	
#include "Movement.generated.h"


struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UMovement();

protected:
virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent() const;

	void Move(const FInputActionValue& Value);
	void Jump();
	void Crouch();

	void StartSprint();
	void StopSprint();

	void SetOnLadder(const bool IsOnLadder);

private:
	UFUNCTION()
	void SprintTick();

	UFUNCTION()
	void StaminaRestorationTick();

	void StartStaminaRestoration();
	void StopStaminaRestoration();

private:
	FTimerManager& GetTimerManager() const;
	void SetMaxWalkSpeed(const float Speed) const;
	bool IsConsumingStamina() const;
	void ConsumeStamina(const float Amount);
	void RestoreStamina(const float Amount);

private:
	UPROPERTY(BlueprintReadOnly, Category=Character, meta = (AllowPrivateAccess = "true"))
	ACharacter* CharacterRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	UPROPERTY()
	float MinStamina;

	UPROPERTY(VisibleAnywhere, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float StaminaRestoreThreshold;

	UPROPERTY()
	bool bIsStaminaBlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float SprintStaminaConsumption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float JumpStaminaConsumption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float StaminaConsumptionRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float StaminaRestoration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float StaminaRestorationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Parameters, meta = (AllowPrivateAccess = "true"))
	float StaminaRestorationDelay;
	
	UPROPERTY()
	FTimerHandle SprintUpdateTimerHandle;
	
	UPROPERTY()
	FTimerHandle StaminaRestorationTimerHandle;

	UPROPERTY()
	bool bIsOnLadder;

	/** Loudness of the events **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Noise", meta=(AllowPrivateAccess = "true"))
	float MoveLoudness = 0.1F;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Noise", meta=(AllowPrivateAccess = "true"))
	float JumpLoudness = 1.0F;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Noise", meta=(AllowPrivateAccess = "true"))
	float SprintLoudness = 1.0F;

};
