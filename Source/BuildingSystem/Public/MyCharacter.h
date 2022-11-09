// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class BUILDINGSYSTEM_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:

	virtual void BeginPlay() override;
	FHitResult PerformLineTrace(float Distance = 650.f , bool DrawDebug = false);

	UPROPERTY(BlueprintReadOnly, Category = "Building")
		bool bInBuildMode = false;


	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly, Category = "Building")
		class UStaticMeshComponent* BuildMesh; 
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Building")
	void  SetBuildEnabled(bool Enabled);
	
	UFUNCTION(BlueprintCallable, Category = "Building")
	bool GetBuildMode() const { return bInBuildMode; }

};
