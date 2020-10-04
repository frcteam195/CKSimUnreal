// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

namespace robosim
{
	namespace zmq_interface
	{
		void init();
		void step();
		float get_motor(int motor);
		void set_encoder(int encoder, float value);
		void set_accelerometer(int accelerometer, float value);
		void set_gyroscope(int gyroscope, float value);
		void set_advanced(int advanced, float value);
		void destroy();
	}
}
//
//#include "Modules/ModuleManager.h"
//
//class FCKSimPluginModule : public IModuleInterface
//{
//public:
//
//	/** IModuleInterface implementation */
//	virtual void StartupModule() override;
//	virtual void ShutdownModule() override;
//
//	bool Tick(float DeltaTime);
//
//private:
//	/** Handle to the test dll we will load */
//	void*	ExampleLibraryHandle;
//};
