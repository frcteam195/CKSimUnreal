// Copyright Epic Games, Inc. All Rights Reserved.

#include "CKSimPlugin.h"
#include "Core.h"

#include "Windows/MinWindows.h"

#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "CKlibzmq/include/zmq.h"

#include "Containers/Ticker.h"

#include <sstream>

#define LOCTEXT_NAMESPACE "FCKSimPluginModule"

FTickerDelegate TickDelegate;
FDelegateHandle TickDelegateHandle;

static void* context;
static void* robot_socket;
static int rc;

bool FCKSimPluginModule::Tick(float DeltaTime)
{
	static char buffer[8000];
	int received_bytes = zmq_recv(robot_socket, buffer, 8000, ZMQ_NOBLOCK);

	if (received_bytes >= 0)
	{
		static int temp = 0;
		if (temp == 0)
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Message", "Got"));
			temp = 1;
		}
		zmq_send(robot_socket, buffer, 8000, 0);
	}
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
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/CKlibzmq/bin/libzmq-v142-mt-4_3_2.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/CKSimPluginLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		context = zmq_ctx_new();
		robot_socket = zmq_socket(context, ZMQ_REP);
		rc = zmq_bind(robot_socket, "tcp://*:25557");

		std::stringstream temp;
		temp << "Whatsit: " << rc;

		FText SomeText = FText::FromString(temp.str().c_str());

		FMessageDialog::Open(EAppMsgType::Ok, SomeText);

		TickDelegate = FTickerDelegate::CreateRaw(this, &FCKSimPluginModule::Tick);
		TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

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

	// Free the dll handle
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCKSimPluginModule, CKSimPlugin)
