#include "sdk.h"

namespace css {
	std::deque< c_module > module_list = { };

	void fill_module_list( ) {
		HMODULE all_modules[ 1024 ] = { };
		DWORD needed;

		if ( K32EnumProcessModules( GetCurrentProcess( ), all_modules, sizeof( all_modules ), &needed ) ) {
			for ( DWORD i = 0; i < ( needed / sizeof( HMODULE ) ); i++ ) {
				MODULEINFO module_info;
				K32GetModuleInformation( GetCurrentProcess( ), all_modules[ i ], &module_info, sizeof( MODULEINFO ) );

				char module_name[ MAX_PATH ];
				K32GetModuleBaseNameA( GetCurrentProcess( ), all_modules[ i ], module_name, sizeof( module_name ) );

				module_list.emplace_back( module_name, c_address( reinterpret_cast< uintptr_t >( module_info.lpBaseOfDll ) ), module_info.SizeOfImage );
			}
		}

		if ( module_list.empty( ) )
			throw std::runtime_error( "failed to fill module list" );
	}

	unsigned long __stdcall init( void* parameter ) {
		try {
			console::open( );
			fill_module_list( );
			console::print( "initalized" );

			while ( !GetAsyncKeyState( VK_DELETE ) )
				std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

			console::close( );
			FreeLibraryAndExitThread( static_cast< HMODULE >( parameter ), 0 );
		}
		catch ( const std::exception& exception ) {
			MessageBoxA( nullptr, exception.what( ), "css", MB_ICONERROR );
			FreeLibraryAndExitThread( static_cast< HMODULE >( parameter ), 1 );
		}
	}
}