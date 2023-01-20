#pragma once

class c_module {
public:
	c_address base_address = 0x0;
	std::string name = "";
	size_t size = 0x0;

	c_module( const std::string& name_, const c_address base_address_, const size_t size_ ) : base_address( base_address_ ), name( name_ ), size( size_ ) { }
	c_signature find_signature( const std::vector< byte >& bytes ) const;
};