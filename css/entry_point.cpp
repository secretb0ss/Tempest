#include "sdk.h"

int __stdcall DllMain( HINSTANCE instance, unsigned long reason, void* /*reserved*/ ) {
	DisableThreadLibraryCalls( instance );

	if ( reason == DLL_PROCESS_ATTACH ) {
		if ( auto thread = CreateThread( nullptr, 0, css::init, instance, 0, nullptr ) )
			CloseHandle( thread );
	}
	
	return 1;
}