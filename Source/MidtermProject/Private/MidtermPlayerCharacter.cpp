// Fill out your copyright notice in the Description page of Project Settings.


#include "MidtermPlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ObjectiveWorldSubsystem.h"
#include "HealthComponent.h"

// Sets default values
AMidtermPlayerCharacter::AMidtermPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AMidtermPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// Called every frame
void AMidtermPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMidtermPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jump
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Crouch
		Input->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMidtermPlayerCharacter::Crouch);
		Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMidtermPlayerCharacter::UnCrouch);

		// Move
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMidtermPlayerCharacter::Move);

		// Look
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMidtermPlayerCharacter::Look);

		// Objectives
		//Input->BindAction(OpenObjectivesAction, ETriggerEvent::Triggered, this, &AMidtermPlayerCharacter::OpenObjectivesWidget);

		// Achievements
		//Input->BindAction(OpenAchievementsAction, ETriggerEvent::Triggered, this, &AMidtermPlayerCharacter::OpenAchievementsWidget);

	}
}

void AMidtermPlayerCharacter::Move(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, MovementValue);
	}
}

void AMidtermPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMidtermPlayerCharacter::Crouch()
{
	ACharacter::Crouch();
}

void AMidtermPlayerCharacter::UnCrouch()
{
	ACharacter::UnCrouch();
}

void AMidtermPlayerCharacter::OpenObjectivesWidget()
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}
}

/*void AMidtermPlayerCharacter::CloseObjectivesWidget()
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->HideObjectiveWidget();
	}
}*/

//void AMidtermPlayerCharacter::OpenAchievementsWidget()
//{
//
//}
//
//void AMidtermPlayerCharacter::CloseAchievementsWidget()
//{
//
//}

// Restart if player falls out of the level
void AMidtermPlayerCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	OnDeath(true);
}

float AMidtermPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AMidtermPlayerCharacter::TakeDamage Damage %.2f"), Damage);
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return Damage;
}

float AMidtermPlayerCharacter::AddHealth(float HealthAmount)
{
	//float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AMidtermPlayerCharacter::HealthAmount Health %.2f"), HealthAmount);
	if (HealthComponent)
	{
		HealthComponent->AddHealth(HealthAmount);
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return HealthAmount;
}

void AMidtermPlayerCharacter::OnDeath(bool IsFellOut)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

void AMidtermPlayerCharacter::CollectKey()
{
	keyCount++;
}