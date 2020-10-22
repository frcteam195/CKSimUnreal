// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RoboSim.generated.h"


UCLASS()
class CKSIMPLUGIN_API UrawRoboSim : public UObject
{
	GENERATED_BODY()
public:
	float Get_Motor(int motor_id);
	void Set_Encoder(int encoder_id, float value);
	void Set_Accelerometer(int accelerometer_id, float value);
	void Set_Gyroscope(int gyroscope_id, float value);
	void Set_Advanced(int advanced_id, float value);
};

/**
 * 
 */
UCLASS()
class URoboSim : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
	UFUNCTION(BlueprintCallable, Category = "Robosim")
	static float Get_Motor(int motor_id);

	UFUNCTION(BlueprintCallable, Category = "Robosim")
	static void Set_Encoder(int encoder_id, float value);

	UFUNCTION(BlueprintCallable, Category = "Robosim")
	static void Set_Accelerometer(int accelerometer_id, float value);

	UFUNCTION(BlueprintCallable, Category = "Robosim")
	static void Set_Gyroscope(int gyroscope_id, float value);

	UFUNCTION(BlueprintCallable, Category = "Robosim")
	static void Set_Advanced(int advanced_id, float value);

};
