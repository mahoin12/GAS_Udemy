// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Aura/Aura.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	
}

void AEnemyCharacter::HighlightActor(UPrimitiveComponent* TouchedComponent)
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AEnemyCharacter::UnHighlightActor(UPrimitiveComponent* TouchedComponent)
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->OnBeginCursorOver.AddDynamic(this, &AEnemyCharacter::HighlightActor);
	GetMesh()->OnEndCursorOver.AddDynamic(this, &AEnemyCharacter::UnHighlightActor);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

