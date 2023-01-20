#include "sdk.h"

namespace modules {
	std::unordered_map< uintptr_t , c_module > module_map = { };

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

				c_module module( module_name, c_address( reinterpret_cast< uintptr_t >( module_info.lpBaseOfDll ) ), module_info.SizeOfImage );

				module_map.insert( { hashing::get_hash( module_name ), module } );
			}
		}

		if ( module_map.empty( ) )
			throw std::runtime_error( "failed to fill module map" );
	}

	c_module find( const std::string name ) {
		const auto it = module_map.find( hashing::get_hash( name ) );

		if ( it == module_map.end( ) )
			throw std::runtime_error( std::format( "failed to find module {}", name ) );

		return it->second;
	}
}