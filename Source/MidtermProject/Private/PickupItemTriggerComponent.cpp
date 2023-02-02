// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemTriggerComponent.h"


UPickupItemTriggerComponent::UPickupItemTriggerComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 50.f;
}

void UPickupItemTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UPickupItemTriggerComponent::OnSphereBeginOverlap);
}

void UPickupItemTriggerComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UPickupItemComponent::OnOverlapBegin"));

	// Checking if it is a First Person Character overlapping
	AMidtermPlayerCharacter* Character = Cast<AMidtermPlayerCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		//OnComponentBeginOverlap.RemoveAll(this);
		//DestroyActor();
	}
}