// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

class IAbilitySystemInterface;
// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(GameplayEffectClass);
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle =TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		/*const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandless.Add(ActiveGameplayEffectHandle, TargetASC);
		}*/
	}
}

void AAuraEffectActor::RemoveEffectFromTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(GameplayEffectClass);
		FGameplayEffectQuery Query;
		Query.EffectSource = this;
		Query.EffectDefinition = GameplayEffectClass;
		TargetASC->RemoveActiveEffects(Query);
	}
}

void AAuraEffectActor::OnOverlapBegin(AActor* TargetActor)
{
	for (TSubclassOf<UGameplayEffect> GameplayEffectClass : BeginOverlapApplyGameplayEffectClasses)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffectClass);
	}
	for (TSubclassOf<UGameplayEffect> GameplayEffectClass : BeginOverlapRemoveGameplayEffectClasses)
	{
		RemoveEffectFromTarget(TargetActor, GameplayEffectClass);
	}
}

void AAuraEffectActor::OnOverlapEnd(AActor* TargetActor)
{
	for (TSubclassOf<UGameplayEffect> GameplayEffectClass : EndOverlapApplyGameplayEffectClasses)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffectClass);
	}
	for (TSubclassOf<UGameplayEffect> GameplayEffectClass : EndOverlapRemoveGameplayEffectClasses)
	{
		RemoveEffectFromTarget(TargetActor, GameplayEffectClass);

		/*UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for(auto& ActiveEffectHandle : ActiveEffectHandless)
		{
			if(ActiveEffectHandle.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle.Key,1);
				HandlesToRemove.Add(ActiveEffectHandle.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandless.FindAndRemoveChecked(Handle);
		}*/
	}
}


