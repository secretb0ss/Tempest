#include "sdk.h"

namespace hashing {
	XXH32_state_t* hash_state = nullptr;

	void init( ) {
		hash_state = XXH32_createState( );
		XXH32_reset( hash_state, 0 );
	}

	void unload( ) {
		XXH32_reset( hash_state, 0 );
	}

	uintptr_t get_hash( const std::string& string ) {
		XXH32_reset( hash_state, 0 );

		if ( XXH32_update( hash_state, string.c_str( ), string.size( ) ) != XXH_OK )
			throw std::runtime_error( "XXH32_update failed" );

		return XXH32_digest( hash_state );
	}
}