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
	ABaseCharacter();

public:
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

public:
	void InteractWithPinLock(FVector& Start, FVector& End);

	UFUNCTION(BlueprintPure)
	bool IsInPinLock() const;

public:
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for interaction with world objects */
	void MouseClick();

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
	TObjectPtr<class UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Flashlight, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> FlashlightArm;

	UPROPERTY(EditDefaultsOnly, Category=Flashlight)
	TSubclassOf<class AFlashlight> FlashlightClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Flashlight, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> Flashlight;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHand> Hand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGrabber> Grabber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPicker> Picker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInteractor> Interactor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHintProducer> HintProducer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetInteractionComponent> WidgetInteraction;
};
