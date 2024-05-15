// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Optional.h"

#include "BasePlayerController.generated.h"

class UInventory;
class UInputAction;

UCLASS()
class CRYPTRAIDER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	
public:
	UFUNCTION(BlueprintCallable)
	FText HintMessage() const;

	TOptional<FKey> GrabKey() const;
	TOptional<FKey> ThrowKey() const;
	TOptional<FKey> InteractKey() const;

	UInventory* GetInventory() const;

	void SetOnLadder(bool Value);
	void SetPinLock(ADoorPinLock* PinLock);
	bool IsInPinLock() const;
	
private:
	/** Called for movement input */
	void Move(const struct FInputActionValue& Value);
	FVector GetWorldLocationFromCursor(FVector& WorldDirection);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Jump();
	void StopJumping();
	
	/** Called for crouch */
	void OnCrouch();
	
	/** Called for interaction with world objects */
	void Grab();
	void Throw();
	void Interact();
	void MouseClick();
	void PickUp();

private:
	TOptional<FKey> GetKeyByAction(const UInputAction* Action) const;

private:
	bool IsOnLadder;

	/** Should really be changed to some general entity is in GUI or sorta **/
	ADoorPinLock* PinLock = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* GrabAction;

	/** Throw Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Mouse Click Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MouseClickAction;

	FTimerHandle RestartTimer;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;
};
