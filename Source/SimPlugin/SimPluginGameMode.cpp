// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimPluginGameMode.h"
#include "SimPluginPawn.h"

ASimPluginGameMode::ASimPluginGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ASimPluginPawn::StaticClass();
}

