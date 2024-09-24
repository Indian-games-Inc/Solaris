#pragma once

#include "Damage/Type/StunDamageType.h"
#include "Engine/DamageEvents.h"
#include "StunDamageEvent.generated.h"

USTRUCT()
struct CRYPTRAIDER_API FStunDamageEvent : public FPointDamageEvent
{
	GENERATED_BODY()

	explicit FStunDamageEvent()
	{
		DamageTypeClass = UStunDamageType::StaticClass();
		StunDuration = 1.f;
	}

	// Add the custom property to pass dynamic data
	UPROPERTY()
	float StunDuration;

	/** ID for this class. NOTE this must be unique for all damage events. */
	static const int32 ClassID = 3; // Set to 3, because 0-2 is occupied by built-in DamageEvent types

	virtual int32 GetTypeID() const override { return FStunDamageEvent::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FStunDamageEvent::ClassID == InID) || FPointDamageEvent::IsOfType(InID); };
};