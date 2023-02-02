// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemComponent.h"
#include "MidtermPlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UPickupItemComponent::UPickupItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPickupItemComponent::BeginPlay()
{
	Super::BeginPlay();

	//TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
	OnComponentBeginOverlap.AddDynamic(this, &UPickupItemComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UPickupItemComponent::OnOverlapEnd);

	// Setup the Sphere Collision
	//SphereRadius = 40.f;
}

void UPickupItemComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UPickupItemComponent::OnOverlapBegin"));
	if (!bActive)
	{
		return;
	}

	if (OtherActor == GetOwner())
	{
		return;
	}

	AMidtermPlayerCharacter* PlayerCharacter = Cast<AMidtermPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		/*SubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		PlayerCharacter->TakeDamage(BaseDamage, DamageEvent, nullptr, GetOwner());
		PlayerCharacter->AddHealth();*/
		//RemoveItemFromWorld();
	}
}

void UPickupItemComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UPickupItemComponent::OnOverlapEnd"));
}

/*void UPickupItemComponent::RemoveItemFromWorld(AActor* PickupItemActor)
{
	// What checks needed?
	PickupItemActor->Destroy();
}*/