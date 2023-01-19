#pragma once

class c_address {
public:
    uintptr_t address = 0;

    c_address( const uintptr_t addr = 0x0 ) : address( addr ) {}

    c_address operator+( const ptrdiff_t offset ) const {
        return { address + offset };
    }

    c_address& operator+=( const ptrdiff_t offset ) {
        address += offset;
        return *this;
    }

    c_address operator-( const ptrdiff_t offset ) const {
        return { address - offset };
    }

    c_address& operator-=( const ptrdiff_t offset ) {
        address -= offset;
        return *this;
    }

    bool operator!( ) const {
        return !address;
    }

    template< typename T >
    T* as_function( ) {
        return reinterpret_cast< T* >( address );
    }

    template < typename T, int L = 1 >
    T dereference( ) {
        if ( !address )
            return T( );

        auto current = address;
        for ( auto i = 0; i < L; i++ ) {
            if ( !current )
                continue;

            current = *reinterpret_cast< uintptr_t* >( current );
        }

        return *reinterpret_cast< T* >( current );
    }
};