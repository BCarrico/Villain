// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "VillainGameplayTags.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "AbilitySystem/VillainAbilitySystemLibrary.h"
#include "AbilitySystem/VillainAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/VillainUserWidget.h"
#include "Villain/Villain.h"

AEnemyBase::AEnemyBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	
	AbilitySystemComponent = CreateDefaultSubobject<UVillainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UVillainAttributeSet>("AttributeSet");

	CharacterClass = ECharacterClass::EnemyClass;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEnemyBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	//TODO: Uncomment weapon if wanting it to be highlighted
	//Weapon->SetRenderCustomDepth(true);
	//Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyBase::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	
	//TODO: Uncomment weapon if wanting it to be highlighted
	//Weapon->SetRenderCustomDepth(false);
}

int32 AEnemyBase::GetPlayerLevel_Implementation()
{
	return Level;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	//GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	/*if (HasAuthority())
	{
		UVillainAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}*/
	
	if(UVillainUserWidget* VillainUserWidget = Cast<UVillainUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		VillainUserWidget->SetWidgetController(this);
	};
	
	if (const UVillainAttributeSet* VillainAS = CastChecked<UVillainAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(VillainAS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
	{
			OnHealthChanged.Broadcast(Data.NewValue);
	});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(VillainAS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
		
		/*AbilitySystemComponent->RegisterGameplayTagEvent(FVillainGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AEnemyBase::HitReactTagChanged
		);*/
		OnHealthChanged.Broadcast(VillainAS->GetHealth());
		OnMaxHealthChanged.Broadcast(VillainAS->GetMaxHealth());
	}
}

void AEnemyBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UVillainAbilitySystemComponent>(GetAbilitySystemComponent())->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnAscRegistered.Broadcast(AbilitySystemComponent);
}

void AEnemyBase::InitializeDefaultAttributes() const
{
	UVillainAbilitySystemLibrary::InitializeDefaultAttributes(CharacterClass, Level, this, AbilitySystemComponent);
	
}