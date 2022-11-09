// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildMeshComponent"));
	
}

FHitResult AMyCharacter::PerformLineTrace(float Distance , bool DrawDebug)
{

	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * Distance; 


	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(hit, Start, End, ECC_Visibility, params);

	if (DrawDebug) {
		DrawDebugLine(GetWorld(), Start , End, FColor::Red);
	}

	

	return hit;
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInBuildMode) {
		PerformLineTrace(650.f , true);
	}
	

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::SetBuildEnabled(bool Enabled)
{
	bInBuildMode = Enabled; 
	if (bInBuildMode) {
		BuildMesh->SetHiddenInGame(false);
	}
	else {
		BuildMesh->SetHiddenInGame(true);
	}
}

