// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Aura/Interface/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class AURA_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	AEnemyCharacter();

public:


protected:
	
	UFUNCTION()
	void HighlightActor(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void UnHighlightActor(UPrimitiveComponent* TouchedComponent);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
