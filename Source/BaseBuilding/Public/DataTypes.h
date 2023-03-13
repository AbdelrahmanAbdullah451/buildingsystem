#pragma once

#include "DataTypes.generated.h"


UENUM(BlueprintType)
enum class EBuildType : uint8 {
	Foundation		UMETA(DisplayName = "Foundation") , 
	Wall			UMETA(DisplayName = "Wall") ,
	Ceiling			UMETA(DisplayName = "Ceiling")
};


USTRUCT(BlueprintType)
struct FBuildingVisualType
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "Building")
		class UStaticMesh* BuildingMesh;


		UPROPERTY(EditDefaultsOnly, Category = "Building")
			EBuildType BuildType;

		UPROPERTY(EditDefaultsOnly, Category = "Building")
			FName FilterCharacter;
};

USTRUCT(BlueprintType)
struct FBuildingSocketData {

	GENERATED_BODY()

		class UInstancedStaticMeshComponent* InstancedComponent;
		int32 Index;
		FName SocketName;
		FTransform SocketTransform;

};