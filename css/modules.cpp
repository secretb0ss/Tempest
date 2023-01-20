#include "sdk.h"

namespace modules {
	std::deque< c_module > module_list = { };

	void init( ) {
		const auto cur_process = GetCurrentProcess( );
		HMODULE all_modules[ 1024 ] = { };
		DWORD needed = 0x0;

		if ( K32EnumProcessModules( cur_process, all_modules, sizeof( all_modules ), &needed ) ) {
			for ( DWORD i = 0; i < ( needed / sizeof( HMODULE ) ); i++ ) {
				MODULEINFO module_info = { };
				char module_name[ MAX_PATH ] = { };
				const auto& module_handle = all_modules[ i ];

				if ( !module_handle )
					continue;

				K32GetModuleInformation( cur_process, module_handle, &module_info, sizeof( MODULEINFO ) );
				K32GetModuleBaseNameA( cur_process, module_handle, module_name, sizeof( module_name ) );

				module_list.emplace_back( module_name, c_address( reinterpret_cast< uintptr_t >( module_info.lpBaseOfDll ) ), module_info.SizeOfImage );
			}
		}

		if ( module_list.empty( ) )
			throw std::runtime_error( "failed to fill module list" );
	}
}