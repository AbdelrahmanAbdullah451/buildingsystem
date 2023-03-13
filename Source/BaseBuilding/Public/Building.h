// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"

#include "Building.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class BASEBUILDING_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuilding();

	UFUNCTION(BlueprintCallable, Category = "Building")
		void DestroyInstance(FVector Fhit);

	UFUNCTION(BlueprintCallable, Category = "Building")
		FTransform GetInstancedSocketTransform(UInstancedStaticMeshComponent* InstancedComponent , int32 MeshIndex, 
			const FName& SocketName );

	int32 GetHitIndex(const FHitResult & Hit);

	FBuildingSocketData GetHitSocketTransform(const FHitResult& Hit ,const FName& Filter, float ValidHitDistance = 100.0f);


	void AddInstance(const FBuildingSocketData& BuildingSocketData , EBuildType BuildType);


protected:
	UPROPERTY(EditAnywhere, Category="Building")
	UInstancedStaticMeshComponent* FoundationInstancedMesh;

	UPROPERTY(EditAnywhere, Category = "Building")
		UInstancedStaticMeshComponent* WallInstancedMesh;

	UPROPERTY(EditAnywhere, Category = "Building")
		UInstancedStaticMeshComponent* CeilingInstancedMesh;

	TArray<FName> MeshInstancedSockets;



	virtual void BeginPlay() override;

	bool isValidSocket(UInstancedStaticMeshComponent * HitComponent ,const FName & Filter , const FName & SocketName);

};
