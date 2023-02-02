// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DealDamageComponent.generated.h"

//class UPrimitiveComponent;

class UDamageType;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MIDTERMPROJECT_API UDealDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDealDamageComponent();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OverBodyIndex, bool bFromSweep, const FHitResult& SweepHit);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OverBodyIndex);

	//UPrimitiveComponent* GetTriggerVolume() const { return TriggerVolumeShape; }

	bool IsActive() const { return bActive; }
	void SetActive(bool IsActive) { bActive = IsActive; }

protected:
	UPROPERTY(EditAnywhere)
	float BaseDamage = 5.0f;

	UPROPERTY(EditAnywhere)
	float BurnDamageMultiplier = 1.5f;

	//UPROPERTY(EditAnywhere, NoClear)
	//UPrimitiveComponent* TriggerVolumeShape;

	bool bActive = true;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
