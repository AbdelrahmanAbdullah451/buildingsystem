// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingVisual.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
ABuildingVisual::ABuildingVisual()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildMeshComponent"));
	RootComponent = BuildMesh;

}

// Called when the game starts or when spawned
void ABuildingVisual::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
}

void ABuildingVisual::SetBuildPosition(const FHitResult& Hit)
{
	BuildMesh->SetWorldLocation(Hit.Location);
}


