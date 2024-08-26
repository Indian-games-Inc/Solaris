#include "GrabberAwareDialogPickStrategy.h"

#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Component/Grabber.h"
#include "GameFramework/Character.h"


void UGrabberAwareDialogPickStrategy::BeginPlay()
{
	Super::BeginPlay();

	if (const auto* Character = GetWorld()->GetFirstPlayerController()->GetCharacter(); IsValid(Character))
	{
		if (auto* Grabber = Character->FindComponentByClass<UGrabber>())
		{
			Grabber->OnGrabbedUpdated.AddUniqueDynamic(this, &UGrabberAwareDialogPickStrategy::OnGrabbedUpdated);
		}
	}
}

bool UGrabberAwareDialogPickStrategy::Check()
{
	return CheckStatus;
}

void UGrabberAwareDialogPickStrategy::OnGrabbedUpdated(const AProjectile* Projectile)
{
	CheckStatus = IsValid(Projectile) && Projectile->GetActorNameOrLabel() == ExpectedItemName;
}
