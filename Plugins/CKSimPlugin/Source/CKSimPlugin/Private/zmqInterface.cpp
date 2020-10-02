// Copyright Epic Games, Inc. All Rights Reserved.

#include "zmqInterface.h"

#include "zmq.h"

static void* robosim_zmq_context = NULL;
static void* publisher_socket = NULL;
static void* replyer_socket = NULL;

static void reinitialize_publisher()
{
	zmq_close(publisher_socket);
	publisher_socket = NULL;
	publisher_socket = zmq_socket(robosim_zmq_context, ZMQ_PUB);
	int rc = zmq_bind(publisher_socket, "tcp://*:10502");
	if (rc <= -1)
	{
		publisher_socket = NULL;
	}
}

static void reinitialize_replyer()
{
	zmq_close(replyer_socket);
	replyer_socket = NULL;
	replyer_socket = zmq_socket(robosim_zmq_context, ZMQ_PUB);
	int rc = zmq_bind(replyer_socket, "tcp://*:10501");
	if (rc <= -1)
	{
		replyer_socket = NULL;
	}
}

void robosim::zmq_interface::init()
{
	robosim_zmq_context = zmq_ctx_new();
	reinitialize_publisher();
	reinitialize_replyer();
}

void robosim::zmq_interface::step()
{
	static int publisher_fail_counter = 0;
	static int replyer_fail_counter = 0;

	if (publisher_socket != NULL)
	{

	}
	else
	{
		publisher_fail_counter = (publisher_fail_counter++) % 100;
		if (publisher_fail_counter == 99)
			reinitialize_publisher();
	}

	if (replyer_socket == NULL)
	{

	}
	else
	{
		replyer_fail_counter = (replyer_fail_counter++) % 100;
		if (replyer_fail_counter == 99)
			reinitialize_replyer();
	}
}

void* robosim::zmq_interface::get_status()
{
	return NULL;
}

void robosim::zmq_interface::set_control(void* input)
{

}

void robosim::zmq_interface::destroy()
{
	zmq_close(publisher_socket);
	zmq_close(replyer_socket);
	zmq_ctx_destroy(robosim_zmq_context);
	publisher_socket = NULL;
	replyer_socket = NULL;
	robosim_zmq_context = NULL;
}


//
//#include "CKSimPlugin.h"
//#include "Core.h"
//
//#include "Windows/MinWindows.h"
//
//#include "Modules/ModuleManager.h"
//#include "Interfaces/IPluginManager.h"
//
//#include "Containers/Ticker.h"
//
//#include <sstream>
//
//#define LOCTEXT_NAMESPACE "FCKSimPluginModule"
//
//FTickerDelegate TickDelegate;
//FDelegateHandle TickDelegateHandle;
//
//
//bool FCKSimPluginModule::Tick(float DeltaTime)
//{
//	static char buffer[8000];
//	int received_bytes = zmq_recv(robot_socket, buffer, 8000, ZMQ_NOBLOCK);
//
//	if (received_bytes >= 0)
//	{
//		static int temp = 0;
//		if (temp == 0)
//		{
//			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Message", "Got"));
//			temp = 1;
//		}
//		zmq_send(robot_socket, buffer, 8000, 0);
//	}
//	return true;
//}
//
//void FCKSimPluginModule::StartupModule()
//{
//	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
//
//	// Get the base directory of this plugin
//	FString BaseDir = IPluginManager::Get().FindPlugin("CKSimPlugin")->GetBaseDir();
//
//	// Add on the relative location of the third party dll and load it
//	FString LibraryPath;
//#if PLATFORM_WINDOWS
//	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/CKlibzmq/bin/libzmq-v142-mt-4_3_3.dll"));
//#elif PLATFORM_MAC
//    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/CKSimPluginLibrary/Mac/Release/libExampleLibrary.dylib"));
//#endif // PLATFORM_WINDOWS
//
//	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
//
//	if (ExampleLibraryHandle)
//	{
//		// Call the test function in the third party library that opens a message box
//		context = zmq_ctx_new();
//		robot_socket = zmq_socket(context, ZMQ_REP);
//		rc = zmq_bind(robot_socket, "tcp://*:25557");
//
//		std::stringstream temp;
//		temp << "Whatsit: " << rc;
//
//		FText SomeText = FText::FromString(temp.str().c_str());
//
//		FMessageDialog::Open(EAppMsgType::Ok, SomeText);
//
//		TickDelegate = FTickerDelegate::CreateRaw(this, &FCKSimPluginModule::Tick);
//		TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
//
//	}
//	else
//	{
//		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
//	}
//}
//
//void FCKSimPluginModule::ShutdownModule()
//{
//	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
//	// we call this function before unloading the module.
//
//	// Free the dll handle
//	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
//	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
//	ExampleLibraryHandle = nullptr;
//}
//
//#undef LOCTEXT_NAMESPACE
//	
//IMPLEMENT_MODULE(FCKSimPluginModule, CKSimPlugin)
