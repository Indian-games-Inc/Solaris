// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "SkeletalMeshInteractable.generated.h"

UCLASS()
class CRYPTRAIDER_API ASkeletalMeshInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkeletalMeshInteractable();
	virtual void Interact() override;
	virtual FString HintMessage() const override;
	virtual bool IsActive() const override;

	void DisablePhysics() const;
	void EnablePhysics() const;

protected:

	//TODO: something common??
	FName GrabbedTag = "Grabbed";
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CloseUpCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Body;
};
