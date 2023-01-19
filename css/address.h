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

    template< typename T >
    T* as_function( ) {
        return reinterpret_cast< T* >( address );
    }

    template< typename T, int L >
    T* dereference( ) {
        T* ptr = reinterpret_cast< T* >( address );

        for ( auto i = 0; i < L; i++ )
            ptr = *ptr;

        return ptr;
    }
};