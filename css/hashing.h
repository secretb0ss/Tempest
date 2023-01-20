#pragma once

namespace hashing {
	void init( );
	void unload( );
	uintptr_t get_hash( const std::string& string );
}