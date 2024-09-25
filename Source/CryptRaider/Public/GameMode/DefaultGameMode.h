#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"


UCLASS()
class CRYPTRAIDER_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);

	void EndGame(bool bIsPlayerWinner) const;
};
