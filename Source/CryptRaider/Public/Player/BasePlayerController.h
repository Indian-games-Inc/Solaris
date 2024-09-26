#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Optional.h"

#include "BasePlayerController.generated.h"

struct FInputActionValue;
class ADoorPinLock;
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
	void SetupInput();

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

public:
	TOptional<FKey> GrabKey() const;
	TOptional<FKey> ThrowKey() const;
	TOptional<FKey> InteractKey() const;

	UInventory* GetInventory() const;
	FVector GetWorldLocationFromCursor(FVector& WorldDirection) const;

private:
	void BindLook(UEnhancedInputComponent* EnhancedInputComponent) const;
	void BindMovement(UEnhancedInputComponent* EnhancedInputComponent) const;
	void BindInteraction(UEnhancedInputComponent* EnhancedInputComponent) const;
	void BindFlashlight(UEnhancedInputComponent* EnhancedInputComponent) const;
	void BindWidgetInteraction(UEnhancedInputComponent* EnhancedInputComponent) const;
	void BindPinLock(UEnhancedInputComponent* EnhancedInputComponent) const;

private:
	TOptional<FKey> GetKeyByAction(const UInputAction* Action) const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

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

	/** Toggle Flashlight Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleFlashlightAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;
};
