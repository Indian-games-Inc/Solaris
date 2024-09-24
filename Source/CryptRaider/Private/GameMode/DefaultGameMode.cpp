#include "GameMode/DefaultGameMode.h"
#include "EngineUtils.h"

void ADefaultGameMode::PawnKilled(APawn* PawnKilled)
{
	UE_LOG(LogTemp, Warning, TEXT("Killed a Pawn: %s"), *PawnKilled->GetName());

	if (APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController()); PlayerController)
	{
		EndGame(false);
	}

	EndGame(true);
}

void ADefaultGameMode::EndGame(bool bIsPlayerWinner) const
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}