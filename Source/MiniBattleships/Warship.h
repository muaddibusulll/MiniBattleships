// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WarshipMovementComponent.h"

#include "Warship.generated.h"

UCLASS()
class MINIBATTLESHIPS_API AWarship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWarship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Returns if a pawn is dead
	UFUNCTION(BlueprintPure)
	bool bIsDead() const;
	// Sends current health state to blueprint UI
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,AController* EventInstigator,AActor* DamageCauser);


private:
	void UseAbility();
	void SwitchActionType();
	
	//ig default hp is 3
	UPROPERTY(EditDefaultsOnly)
	int16 MaxHealthPoints = 3;

	// Defines if a pawn is moving or attacking
	bool isActionMoving = 1;

	int16 CurrentHealthPoints;

	UWarshipMovementComponent* MovementComponent;
};
