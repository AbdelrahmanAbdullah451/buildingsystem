// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseBuildingGameMode.h"
#include "BaseBuildingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABaseBuildingGameMode::ABaseBuildingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
