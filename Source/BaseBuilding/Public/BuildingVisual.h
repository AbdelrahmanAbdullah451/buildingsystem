// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingVisual.generated.h"

class UStaticMeshComponent;

UCLASS()
class BASEBUILDING_API ABuildingVisual : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuildingVisual();

protected:

	virtual void BeginPlay() override;

public:	

};
