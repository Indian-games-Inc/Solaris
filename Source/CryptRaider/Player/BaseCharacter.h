// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/Movement.h"
#include "Components/Health.h"
#include "BaseCharacter.generated.h"

class ADoorPinLock;
class IInteractable;
class UInputAction;

UCLASS()
class CRYPTRAIDER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

public:
	class UGrabber* GetGrabber() const;

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

public:
	void InteractWithPinLock(FVector& Start, FVector& End);

	UFUNCTION(BlueprintPure)
	FText HintMessage() const;

	UFUNCTION(BlueprintPure)
	bool IsInPinLock() const;

	UFUNCTION(BlueprintCallable)
	UMovement* GetMovement() const;

	UFUNCTION(BlueprintCallable)
	UHealth* GetHealth() const;

public:
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for interaction with world objects */
	void Grab();
	void Throw();
	void Interact();
	void MouseClick();
	void ToggleFlashlight();

	TOptional<struct FInventoryItemWrapper> PickUp();
	FText ConstructHintFor(const IInteractable* Interactable) const;
	void SetPinLock(TSoftObjectPtr<ADoorPinLock> PinLock);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMovement> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UHealth> Health;

	/** Should really be changed to some general entity is in GUI or sorta **/
	TSoftObjectPtr<ADoorPinLock> PinLock = nullptr;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Flashlight, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* FlashlightArm;

	UPROPERTY(EditDefaultsOnly, Category=Flashlight)
	TSubclassOf<class AFlashlight> FlashlightClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Flashlight, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* Flashlight;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UHand* Hand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UGrabber* Grabber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPicker* Picker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractor* Interactor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Noise", meta=(AllowPrivateAccess = "true"))
	float FlashlightLoudness = 0.1F;
};
