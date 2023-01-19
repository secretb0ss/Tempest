#pragma once

class c_module {
public:
	c_address base_address = 0x0;
	std::string name = "";
	size_t size = 0x0;

	c_module( const std::string& name, const c_address base_address, const size_t size ) : base_address( base_address ), name( name ), size( size ) { }
};