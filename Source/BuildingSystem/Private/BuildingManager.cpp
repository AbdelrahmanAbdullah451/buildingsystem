// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManager.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ABuildingManager::ABuildingManager()
{
	PrimaryActorTick.bCanEverTick = false;

	FoundationInstacedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FoundationInstacedMesh"));

	RootComponent = FoundationInstacedMesh; 
}

// Called when the game starts or when spawned
void ABuildingManager::BeginPlay()
{
	Super::BeginPlay();

	FTransform MeshTransform = FTransform();

	for (size_t i = 0; i < 3; i++)
	{
		FoundationInstacedMesh->AddInstance(MeshTransform);

		FVector MeshLocation = MeshTransform.GetLocation();

		MeshLocation.Z += 250;

		MeshTransform.SetLocation(MeshLocation);
	}

	
	
}

void ABuildingManager::DestroyInstance(FVector HitPoint)
{

	const TArray<int32> HitIndexes =  FoundationInstacedMesh->GetInstancesOverlappingSphere(HitPoint , 1.0f);
	if (HitIndexes.Num() > 0)
	{
		FoundationInstacedMesh->RemoveInstance(HitIndexes[0]);
	}
}

FTransform ABuildingManager::GetInstanceSocketTransform(int32 MeshIndex, UInstancedStaticMeshComponent* InstancedComponent, const FName& SocketName  , bool& Success, bool WorldSpace)
{
	Success = true;
	if (InstancedComponent && InstancedComponent->IsValidInstance(MeshIndex)) {

		// getting instance transform 
		FTransform InstanceTransform = FTransform();
		InstancedComponent->GetInstanceTransform(MeshIndex , InstanceTransform, false);
		


		//getting socket trasform
		FTransform SocketTransform = InstancedComponent->GetSocketTransform(SocketName, RTS_Component);
		if (SocketTransform.Equals(FTransform())) {
			Success = false;
			return FTransform();
		}


		// Making socket transform relative to instance transform
		FTransform RelativeSocketTransform = UKismetMathLibrary::MakeRelativeTransform(SocketTransform, InstanceTransform);
		FVector RelativeSocketLocation = RelativeSocketTransform.GetLocation();

		if (WorldSpace) {

			RelativeSocketLocation.Z = SocketTransform.GetLocation().Z;
			InstancedComponent->GetInstanceTransform(MeshIndex, InstanceTransform, true);
			FVector WorldLocation = InstanceTransform.GetLocation() + RelativeSocketLocation;	
			RelativeSocketTransform.SetLocation(WorldLocation);
			return RelativeSocketTransform;
		}

		RelativeSocketLocation.Z = InstanceTransform.GetLocation().Z + SocketTransform.GetLocation().Z; 
		RelativeSocketTransform.SetLocation(RelativeSocketLocation);
		

		return RelativeSocketTransform; 
		
	}
	Success = false;
	return FTransform();
}


