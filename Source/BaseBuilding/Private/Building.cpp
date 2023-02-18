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

	WallInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallInstancedStaticMesh"));
}


// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	FoundationInstancedMesh->AddInstance(FTransform());
}

void ABuilding::AddInstance(const FTransform& ActorTransform , EBuildType BuildType)
{
	switch (BuildType) {
		case EBuildType::Foundation :
			FoundationInstancedMesh->AddInstanceWorldSpace(ActorTransform);
			break;
		case EBuildType::Wall:
			WallInstancedMesh->AddInstanceWorldSpace(ActorTransform);
			break;
	}
	
}



void ABuilding::DestroyInstance(FVector Fhit)
{
	TArray<int32> HitObjects = FoundationInstancedMesh->GetInstancesOverlappingSphere(Fhit, 1.0f);

	if (HitObjects.Num() > 0) {
		FoundationInstancedMesh->RemoveInstance(HitObjects[0]);
	}

}

FTransform ABuilding::GetInstancedSocketTransform(UInstancedStaticMeshComponent* InstancedComponent,int32 MeshIndex,
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

int32 ABuilding::GetHitIndex(const FHitResult& Hit)
{
	TArray<int32> HitIndex = FoundationInstancedMesh->GetInstancesOverlappingSphere(Hit.Location , 10.0f);
	DrawDebugSphere(GetWorld() , Hit.Location , 10.0f , 10 , FColor::Blue );
	//UE_LOG(LogTemp, Error, TEXT("Hit Index: %s"), *Hit.GetActor()->GetName());
	if (HitIndex.Num() > 0 && HitIndex.Num()) {
		return HitIndex[0];
	}
	return -1;
}

FTransform ABuilding::GetHitSocketTransform(const FHitResult& Hit, float ValidHitDistance)
{

	int32 HitIndex = GetHitIndex(Hit);
	if (HitIndex != -1) {
		TArray<FName> SocketNames = FoundationInstancedMesh->GetAllSocketNames();
		bool isSuccessfull = false;
		/*for (const FName x : SocketNames) {
			UE_LOG(LogTemp, Warning, TEXT("Hlmy : %s"), *x.ToString());
		}*/
		for (const FName x : SocketNames) {
			FTransform SocketTransform = GetInstancedSocketTransform(FoundationInstancedMesh ,HitIndex , x , isSuccessfull, true);
			if (FVector::Distance(SocketTransform.GetLocation(),Hit.Location) <= ValidHitDistance) {

				return SocketTransform;
			}
			else {
				if (helmy) {
					helmy = false;
					UE_LOG(LogTemp, Warning, TEXT("Hlmy : %s"), *x.ToString());
				}
			}
		}
	}

	return  FTransform();
}


/*	FVector SocketLocation = FoundationInstancedMesh->GetSocketTransform(SocketNames[i]).GetLocation();

			double CurrentDistance = FVector::Distance(SocketLocation, Hit.Location);

			if (double newDis = FVector::Distance(FoundationInstancedMesh->GetSocketTransform(SocketNames[i]).GetLocation(), Hit.Location)) {

}*/