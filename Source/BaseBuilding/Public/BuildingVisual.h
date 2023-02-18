// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"

#include "BuildingVisual.generated.h"

class UStaticMeshComponent;
class ABuilding;
class UMaterialInstance;
UCLASS()
class BASEBUILDING_API ABuildingVisual : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuildingVisual();

protected:

	virtual void BeginPlay() override;

public:	
	void SetBuildPosition(const FHitResult& Hit);
	void SpawnBuilding();
	void CycleMeshes();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
		UStaticMeshComponent* BuildMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
		TSubclassOf<ABuilding> BuildingClass;


	UPROPERTY(EditDefaultsOnly, Category = "Building")
		TArray<FBuildingVisualType > BuildingTypes;

	ABuilding* GetHitBuilding(const FHitResult& Hit);

	uint8 BuildingTypeIndex;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UMaterialInstance* MaterialTrue;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UMaterialInstance* MaterialFalse;

	bool bIsMaterialTrue;

	ABuilding* InteractingBuilding;

	
};
