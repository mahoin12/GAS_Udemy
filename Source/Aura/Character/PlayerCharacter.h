// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AURA_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	APlayerCharacter();


public:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
