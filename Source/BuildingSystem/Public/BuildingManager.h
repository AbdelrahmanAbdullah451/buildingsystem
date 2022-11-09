// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingManager.generated.h"

class UInstancedStaticMeshCompnent;
UCLASS()
class BUILDINGSYSTEM_API ABuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingManager();

protected:
	UPROPERTY(BlueprintReadOnly,Category ="Building")
		UInstancedStaticMeshComponent* FoundationInstacedMesh; 


	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Building")
		void DestroyInstance(FVector Hit); 

	UFUNCTION(BlueprintCallable, Category = "Building")
		FTransform GetInstanceSocketTransform(int32 MeshIndex , UInstancedStaticMeshComponent * InstancedComponent ,
			const FName& SocketName  , bool& Success, bool WorldSpace = false);
};
