// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleshipsPlayerController.h"
#include "DrawDebugHelpers.h"

void ABattleshipsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
	bShowMouseCursor = true;
}

void ABattleshipsPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABattleshipsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Ability"), EInputEvent::IE_Pressed, this, &ABattleshipsPlayerController::AbilityTrigger);
	InputComponent->BindAction(TEXT("MoveAttackSwitch"), EInputEvent::IE_Pressed, this, &ABattleshipsPlayerController::SwitchActionType);
	InputComponent->BindAction(TEXT("MouseClick"), EInputEvent::IE_Pressed, this, &ABattleshipsPlayerController::OnMouseClick);
}

void ABattleshipsPlayerController::SetControlledPawn(FHitResult Hit) 
{
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, FString::Printf(TEXT("Hit: %s"), *ActorHit->GetName()));
		ActivePawn = Cast<AWarship>(ActorHit);
	}
}

void ABattleshipsPlayerController::UseAbility(AWarship* User)
{
	if (User == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("%s has used an ability!"), *User->GetName());
	//Actor component of a specific ability :)
}

void ABattleshipsPlayerController::OnMouseClick()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
	SetControlledPawn(HitResult);
}

void ABattleshipsPlayerController::AbilityTrigger() {
	if (ActivePawn == nullptr) return;
	UseAbility(ActivePawn);
}

void ABattleshipsPlayerController::SwitchActionType()
{
	//true - Action = move
	//false - Action = attack
	isActionMoving = !isActionMoving;
	UE_LOG(LogTemp, Warning, TEXT("Switched the action type to %d"), isActionMoving);
}
