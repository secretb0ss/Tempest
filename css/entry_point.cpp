#include "sdk.h"

int __stdcall DllMain( HINSTANCE instance, unsigned long reason, void* /*reserved*/ ) {
	if ( reason == DLL_PROCESS_ATTACH ) {
		const std::unique_ptr< void, decltype( &CloseHandle ) > thread( CreateThread( nullptr, 0, css::init, instance, 0, nullptr ), &CloseHandle );

		if ( !thread )
			MessageBoxA( nullptr, "failed to create init thread", "dllmain", MB_ICONERROR );
	}
	
	return 1;
}