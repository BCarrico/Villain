// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"

#include "Character/VillainCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	//WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	//WeaponMesh->MarkRenderStateDirty(); // Forces refresh
	//EnableCustomDepth(true);
	
	AreaSphere = CreateDefaultSubobject<USphereComponent>("AreaSphere");
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>("PickupWidget");
	PickupWidget->SetupAttachment(RootComponent);
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	//TODO: Check these below collision settings??
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
	}
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AVillainCharacter* VillainCharacter = Cast<AVillainCharacter>(OtherActor))
	{
		PickupWidget->SetVisibility(true);
		//VillainCharacter->SetOverlappingWeapon(this);
	}	
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AVillainCharacter* VillainCharacter = Cast<AVillainCharacter>(OtherActor))
	{
		PickupWidget->SetVisibility(false);
		//VillainCharacter->SetOverlappingWeapon(this);
	}	
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

