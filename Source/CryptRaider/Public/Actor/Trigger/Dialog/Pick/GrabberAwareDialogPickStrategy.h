#pragma once

#include "CoreMinimal.h"
#include "ConditionalDialogPickStrategy.h"
#include "GrabberAwareDialogPickStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabberAwareDialogPickStrategy : public UConditionalDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
public:
	virtual bool Check() override;

private:
	UFUNCTION()
	void OnGrabbedUpdated(const class AProjectile* Projectile);
	
private:
	UPROPERTY(Category="ConditionalDialogPickStrategy", EditInstanceOnly, BlueprintReadWrite,
		meta=(AllowPrivateAccess="true"))
	FName ExpectedItemName;

	UPROPERTY(VisibleInstanceOnly)
	bool CheckStatus = false;
};
