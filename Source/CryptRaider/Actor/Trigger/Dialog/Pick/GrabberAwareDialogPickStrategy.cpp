#include "GrabberAwareDialogPickStrategy.h"

#include "CryptRaider/Component/Grabber.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UGrabberAwareDialogPickStrategy::Check()
{
	const auto Grabber = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetGrabber();
	return Grabber->IsGrabbing() && Grabber->GetGrabbedItemName() == ItemName;
}
