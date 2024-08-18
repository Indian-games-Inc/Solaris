// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

float UHealth::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void UHealth::TakeDamage(float Damage)
{
	Damage = FMath::Min(Health, Damage);
	Health -= Damage;
}

bool UHealth::IsDead() const
{
	return Health <= 0;
}

float UHealth::GetMaxHealth() const
{
	return MaxHealth;
}