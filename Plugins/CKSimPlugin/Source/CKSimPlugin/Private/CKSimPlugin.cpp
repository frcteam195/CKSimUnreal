// Copyright Epic Games, Inc. All Rights Reserved.

#include "CKSimPlugin.h"
#include "Core.h"

#include "Windows/MinWindows.h"

#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "zmq.h"
#include "zmqInterface.h"

#include "Containers/Ticker.h"

#include <sstream>

#define LOCTEXT_NAMESPACE "FCKSimPluginModule"

FTickerDelegate TickDelegate;
FDelegateHandle TickDelegateHandle;

bool FCKSimPluginModule::Tick(float DeltaTime)
{
	robosim::zmq_interface::step();
	return true;
}

void FCKSimPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("CKSimPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/CKlibzmq/bin/libzmq-v142-mt-4_3_3.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/CKSimPluginLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Starting up CK plugin"));

	if (ExampleLibraryHandle)
	{
		TickDelegate = FTickerDelegate::CreateRaw(this, &FCKSimPluginModule::Tick);
		TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

		robosim::zmq_interface::init();
		UE_LOG(LogTemp, Warning, TEXT("init complete"));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FCKSimPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	robosim::zmq_interface::destroy();

	// Free the dll handle
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCKSimPluginModule, CKSimPlugin)
