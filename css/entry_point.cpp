#include "sdk.h"

int __stdcall DllMain( HINSTANCE instance, unsigned long reason, void* /*reserved*/ ) {
	if ( reason == DLL_PROCESS_ATTACH )
		std::unique_ptr< void, decltype( &CloseHandle ) >( CreateThread( nullptr, 0, css::init, instance, 0, nullptr ), &CloseHandle );
	
	return 1;
}