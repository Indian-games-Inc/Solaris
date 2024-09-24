// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/Interactable.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ABaseInteractable();

	virtual void Interact() override;
	virtual FString HintMessage() const override;
	virtual bool IsActive() const override;

	void DisablePhysics() const;
	void EnablePhysics() const;

	UMeshComponent* GetBody() const;

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                      AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	                   UPrimitiveComponent* OtherComp,
	                   FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LoudnessOfOnHit = 0.5F;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float VelocityLimit = 100.0F;
};
