// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

namespace robosim
{
	namespace zmq_interface
	{
		void init();
		void step();
		void * get_status();
		void set_control(void * input);
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
