// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
		FTransform GetInstancedSocket(UInstancedStaticMeshComponent* InstancedComponent , int32 MeshIndex, 
			const FName& SocketName , bool& Success, bool WorldSpace = false);

protected:
	UPROPERTY(EditAnywhere, Category="Building")
	UInstancedStaticMeshComponent* FoundationInstancedMesh;


	virtual void BeginPlay() override;

};
