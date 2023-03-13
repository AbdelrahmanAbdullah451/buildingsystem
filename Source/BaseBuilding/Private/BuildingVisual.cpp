// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingVisual.h"

#include "Components/StaticMeshComponent.h"
#include "Building.h"


ABuildingVisual::ABuildingVisual()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildMeshComponent"));
	RootComponent = BuildMesh;

	BuildingTypeIndex = 0;

	bIsMaterialTrue = false;
	bReturnedMesh = true;
}

void ABuildingVisual::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);

	if (BuildingTypes[BuildingTypeIndex].BuildingMesh) {
		BuildMesh->SetStaticMesh(BuildingTypes[BuildingTypeIndex].BuildingMesh);
	}

	if (MaterialTrue) {

		bIsMaterialTrue = true;
		BuildMesh->SetMaterial(0, MaterialTrue);
	}
}

ABuilding* ABuildingVisual::GetHitBuilding(const FHitResult& Hit)
{
	return Cast<ABuilding>(Hit.GetActor());
}

void ABuildingVisual::SetMeshTo(EBuildType BuildType)
{
	bReturnedMesh = false;
	for (const FBuildingVisualType& Building: BuildingTypes) {
		if (Building.BuildType == BuildType) {
			BuildMesh->SetStaticMesh(Building.BuildingMesh);
			return;
		}

	}
}

void ABuildingVisual::ReturnMeshToSelected()
{
	bReturnedMesh = true;
	if (BuildingTypes[BuildingTypeIndex].BuildingMesh) {
		BuildMesh->SetStaticMesh(BuildingTypes[BuildingTypeIndex].BuildingMesh);
	}
}





void ABuildingVisual::SetBuildPosition(const FHitResult& Hit)
{
	if (Hit.bBlockingHit) {

		
		this->SetActorHiddenInGame(false);
		InteractingBuilding = GetHitBuilding(Hit);
		if (InteractingBuilding) {
			if (!bReturnedMesh)
			{
				ReturnMeshToSelected();
			}

			 SocketData = InteractingBuilding->GetHitSocketTransform(Hit ,BuildingTypes[BuildingTypeIndex].FilterCharacter, 75.0f);
			if (!SocketData.SocketTransform.Equals(FTransform())) {
				SetActorTransform(SocketData.SocketTransform);
				if (MaterialTrue && !bIsMaterialTrue) {
					bIsMaterialTrue = true;
					BuildMesh->SetMaterial(0 , MaterialTrue);
				}
				return;
			}
			else {
				BuildMesh->SetWorldLocation(Hit.Location);
				if (MaterialFalse && bIsMaterialTrue) {
					bIsMaterialTrue = false;
					BuildMesh->SetMaterial(0, MaterialFalse);
				}
			}
		}
		else {
			if(bReturnedMesh){
				SetMeshTo(EBuildType::Foundation);
			}
			BuildMesh->SetWorldLocation(Hit.Location);

		}
	}
	else {
		InteractingBuilding = nullptr;
		this->SetActorHiddenInGame(true);
	}
}

void ABuildingVisual::SpawnBuilding()
{
	if (BuildingClass && !IsHidden() ) {
		if (InteractingBuilding ) {
			if (bIsMaterialTrue) {
				InteractingBuilding->AddInstance(SocketData , BuildingTypes[BuildingTypeIndex].BuildType);
			}
			
		}
		else {
			GetWorld()->SpawnActor<ABuilding>(BuildingClass, GetActorTransform());
		}
	}
}

void ABuildingVisual::CycleMeshes()
{
	if (bReturnedMesh)
	{
		if (++BuildingTypeIndex >= BuildingTypes.Num()) {
			BuildingTypeIndex = 0;
		}
		if (BuildingTypes[BuildingTypeIndex].BuildingMesh) {
			BuildMesh->SetStaticMesh(BuildingTypes[BuildingTypeIndex].BuildingMesh);
		}
	}
}



