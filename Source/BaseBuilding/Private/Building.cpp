// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABuilding::ABuilding()
{

	PrimaryActorTick.bCanEverTick = false;

	FoundationInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FoundationInstancedStaticMesh"));
 	
	RootComponent = FoundationInstancedMesh;

}


// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	FTransform MeshTransform = FTransform();
	for (uint8 i = 0; i < 3; i++)
	{
		FoundationInstancedMesh->AddInstance(MeshTransform);
		FVector MeshLocation = MeshTransform.GetLocation();
		MeshLocation.Z += 250;
		MeshTransform.SetLocation(MeshLocation);
	}
}



void ABuilding::DestroyInstance(FVector Fhit)
{
	TArray<int32> HitObjects = FoundationInstancedMesh->GetInstancesOverlappingSphere(Fhit, 1.0f);

	if (HitObjects.Num() > 0) {
		FoundationInstancedMesh->RemoveInstance(HitObjects[0]);
	}

}

FTransform ABuilding::GetInstancedSocket(UInstancedStaticMeshComponent* InstancedComponent,int32 MeshIndex,
	const FName& SocketName, bool& Success, bool WorldSpace)
{
	Success = true;
	if (InstancedComponent && InstancedComponent->IsValidInstance(MeshIndex)) {

		FTransform InstanceTransform = FTransform();
		InstancedComponent->GetInstanceTransform(MeshIndex,InstanceTransform , false);

		

		FTransform SocketTransform = InstancedComponent->GetSocketTransform(SocketName, RTS_Component);
		if (SocketTransform.Equals(FTransform())) {
			Success = false;
			return FTransform();
		}
		FTransform RelativeTransform = UKismetMathLibrary::MakeRelativeTransform(SocketTransform , InstanceTransform);

		FVector RelativeLocation = RelativeTransform.GetLocation();

		if (WorldSpace) {
			RelativeLocation.Z = SocketTransform.GetLocation().Z;
			InstancedComponent->GetInstanceTransform(MeshIndex  , InstanceTransform, true);
			FVector WorldLocation = InstanceTransform.GetLocation() + RelativeLocation;
			RelativeTransform.SetLocation(WorldLocation);
			return RelativeTransform;
		}

		RelativeLocation.Z = InstanceTransform.GetLocation().Z + SocketTransform.GetLocation().Z;

		RelativeTransform.SetLocation(RelativeLocation);

		return RelativeTransform;
	}
	Success = false;
	return FTransform();
}