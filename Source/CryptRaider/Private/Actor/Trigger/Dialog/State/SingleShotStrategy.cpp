// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/Dialog/State/SingleShotStrategy.h"


bool USingleShotStrategy::IsActive()
{
	return Active;
}

void USingleShotStrategy::OnTrigger()
{
	if (Active)
	{
		Active = false;	
	}
}
