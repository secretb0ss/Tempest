#include "sdk.h"

namespace console {
    std::ofstream stdout_stream = { };

    void open( ) {
        if ( !AllocConsole( ) )
            throw std::runtime_error( "failed to allocate console" );

        stdout_stream.open( std::filesystem::path( "CONOUT$" ), std::ios::out );

        if ( !stdout_stream.is_open( ) )
            throw std::runtime_error( "failed to open output stream" );

        std::cout.rdbuf( stdout_stream.rdbuf( ) );
    }

    void close( ) {
        stdout_stream.flush( );
        stdout_stream.close( );

        if ( !FreeConsole( ) )
            throw std::runtime_error( "failed to free console" );
    }
}