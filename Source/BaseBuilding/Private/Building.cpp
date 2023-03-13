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

	CeilingInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CeilingInstancedStaticMesh"));
}


// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	FoundationInstancedMesh->AddInstance(FTransform());

	 MeshInstancedSockets = FoundationInstancedMesh->GetAllSocketNames();
	 MeshInstancedSockets.Append(WallInstancedMesh->GetAllSocketNames());
	 MeshInstancedSockets.Append(WallInstancedMesh->GetAllSocketNames());
}


void ABuilding::AddInstance(const FBuildingSocketData& BuildingSocketData ,EBuildType BuildType)
{

	//if (BuildingSocketData.InstancedComponent) {
	//	BuildingSocketData.InstancedComponent->AddInstanceWorldSpace(BuildingSocketData.SocketTransform);
	//}

	switch (BuildType) {
		case EBuildType::Foundation :
			FoundationInstancedMesh->AddInstanceWorldSpace(BuildingSocketData.SocketTransform);
			break;
		case EBuildType::Wall:
			WallInstancedMesh->AddInstanceWorldSpace(BuildingSocketData.SocketTransform);
			break;
		case EBuildType::Ceiling:
			CeilingInstancedMesh->AddInstanceWorldSpace(BuildingSocketData.SocketTransform);
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

FTransform ABuilding::GetInstancedSocketTransform(UInstancedStaticMeshComponent* InstancedComponent,int32 InstanceIndex,
	const FName& SocketName)
{
	if (InstancedComponent && InstancedComponent->IsValidInstance(InstanceIndex)) {

		FTransform InstanceTransform = FTransform();
		InstancedComponent->GetInstanceTransform(InstanceIndex, InstanceTransform,true);
		FTransform SocketTransform = InstancedComponent->GetSocketTransform(SocketName,RTS_Component);
		InstanceTransform = SocketTransform * InstanceTransform;

		return InstanceTransform;
	}

	/*Success = true;
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
	Success = false;*/
	return FTransform();
}

int32 ABuilding::GetHitIndex(const FHitResult& Hit)
{
	DrawDebugSphere(GetWorld() , Hit.Location , 10.0f , 10 , FColor::Blue );
	return Hit.Item;
	
}


bool ABuilding::isValidSocket(UInstancedStaticMeshComponent* HitComponent, const FName& Filter, const FName& SocketName)
{
	bool bSuccess = true;
	if (!HitComponent->DoesSocketExist(SocketName)) {
		bSuccess = false;
		return bSuccess;
	}
	FString FilterString = Filter.ToString();
	FString SocketNameString = SocketName.ToString();
	if (!SocketNameString.Contains(FilterString,ESearchCase::CaseSensitive)) {
		bSuccess = false;
	}
	return bSuccess;

}

FBuildingSocketData ABuilding::GetHitSocketTransform(const FHitResult& Hit ,const FName& Filter,float ValidHitDistance)
{

	FBuildingSocketData SocketData = FBuildingSocketData();
	if (UInstancedStaticMeshComponent* HitComponent = Cast<UInstancedStaticMeshComponent>(Hit.GetComponent())) {

		int32 HitIndex = GetHitIndex(Hit);
		
		if (HitIndex != -1) {
		
			/*for (const FName x : SocketNames) {
				UE_LOG(LogTemp, Warning, TEXT("Hlmy : %s"), *x.ToString());
			}*/
			for (const FName& x : MeshInstancedSockets) {

				if (isValidSocket(HitComponent , Filter , x)) {
					FTransform SocketTransform = GetInstancedSocketTransform(HitComponent, HitIndex, x);
					if (FVector::Distance(SocketTransform.GetLocation(), Hit.Location) <= ValidHitDistance) {

						SocketData.Index = HitIndex;
						SocketData.InstancedComponent = HitComponent;
						SocketData.SocketName = x;
						SocketData.SocketTransform = SocketTransform;
						return SocketData;
					}
				}
			
			}
		}
	}

	return SocketData;
}


/*	FVector SocketLocation = FoundationInstancedMesh->GetSocketTransform(SocketNames[i]).GetLocation();

			double CurrentDistance = FVector::Distance(SocketLocation, Hit.Location);

			if (double newDis = FVector::Distance(FoundationInstancedMesh->GetSocketTransform(SocketNames[i]).GetLocation(), Hit.Location)) {

}*/