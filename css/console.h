#pragma once

namespace console {
	void open( );
	void close( );

    template<typename T, typename... Args>
    void print( T first, Args... args ) {
        if ( std::cout.good( ) ) {
            std::cout << first;
            ( std::cout << ... << args );
            std::cout << std::endl;
        }
    }
}