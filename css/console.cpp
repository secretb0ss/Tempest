#include "sdk.h"

namespace console {
	FILE* stdout_stream = nullptr;

	void open( ) {
		if ( !AllocConsole( ) )
			throw std::runtime_error( "failed to allocate console" );
		
		freopen_s( &stdout_stream, "CONOUT$", "w", stdout );

		if ( !stdout_stream )
			throw std::runtime_error( "failed to open output stream" );
	}

	void close( ) {
		if ( fclose( stdout_stream ) )
			throw std::runtime_error( "failed to close output stream" );

		if ( !FreeConsole( ) )
			throw std::runtime_error( "failed to free console" );
	}
}