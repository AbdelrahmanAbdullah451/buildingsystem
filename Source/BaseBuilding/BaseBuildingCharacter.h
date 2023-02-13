// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseBuildingCharacter.generated.h"

class UStaticMeshComponent;
class ABuildingVisual;

UCLASS(config=Game)
class ABaseBuildingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ABaseBuildingCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;


	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
		bool bInBuildMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
		TSubclassOf<ABuildingVisual> BuildingVisualClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
		ABuildingVisual* Builder;

public:

	virtual void Tick(float DeltaTime) override;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category = "Building")
		void SetBuildMode(bool Enabled);

	UFUNCTION(BlueprintCallable, Category = "Building")
		bool GetBuildMode() const { return bInBuildMode; };

	UFUNCTION(BlueprintCallable, Category = "Building")
		void SpawnBuilding();



protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FHitResult PerformLineTrace(float Distance = 650.0f , bool DrawDebug = false);

};

