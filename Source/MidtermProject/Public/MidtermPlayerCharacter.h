// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HealthComponent.h"
#include "MidtermPlayerCharacter.generated.h"

UCLASS(config = Game)
class MIDTERMPROJECT_API AMidtermPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		// Mapping context
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	// Move action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	// Look action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	// Jump action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	// Crouch action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CrouchAction;

	// Open objective menu action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* OpenObjectivesAction;

	// Open achievement menu action
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* OpenAchievementsAction;*/

	int keyCount = 0;

public:
	// Sets default values for this character's properties
	AMidtermPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Crouch();
	void UnCrouch();

	void OpenObjectivesWidget();
	void CloseObjectivesWidget();

	//void OpenAchievementsWidget();
	//void CloseAchievementsWidget();

	void OnDeath(bool IsFellOut);

	UFUNCTION(BlueprintCallable)
	void CollectKey();

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when actor falls out of the world 'safely'
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	UFUNCTION(BlueprintCallable)
		float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
		float AddHealth(float HealthAmount);
};