#include "sdk.h"

namespace css {
	unsigned long __stdcall init( void* parameter ) {
		try {
			console::open( );
			hashing::init( );
			modules::init( );
			console::print( "initalized" );

			while ( !GetAsyncKeyState( VK_DELETE ) )
				std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

			console::close( );
			hashing::unload( );
			FreeLibraryAndExitThread( static_cast< HMODULE >( parameter ), 0 );
		}
		catch ( const std::exception& exception ) {
			MessageBoxA( nullptr, exception.what( ), "css", MB_ICONERROR );
			FreeLibraryAndExitThread( static_cast< HMODULE >( parameter ), 1 );
		}
	}
}