#include "sdk.h"

c_signature c_module::find_signature( const std::vector< byte >& bytes ) const {
	const auto module_bytes = reinterpret_cast< byte* >( this->base_address( ) );
	const auto size_of_bytes = bytes.size( );
	const auto byte_array = bytes.data( );
	auto valid = false;

	for ( size_t i = 0; i < this->size - size_of_bytes; i++ ) {
		if ( !module_bytes[ i ] )
			continue;

		for ( size_t s = 0; s < size_of_bytes; s++ ) {
			if ( byte_array[ s ] == 0xAE )
				continue;

			if ( module_bytes[ s + i ] != byte_array[ s ] ) {
				valid = false;
				break;
			}
			else
				valid = true;
		}

		if ( valid )
			return { this->base_address + i };
	}

	return { };
}