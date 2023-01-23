#pragma once

class c_module {
public:
	c_address base_address = 0x0;
	std::string name = "";
	size_t size = 0x0;
	std::unordered_map< uintptr_t, std::pair< std::string, uintptr_t > > interface_map = { };

	c_module( const std::string& name_, const c_address base_address_, const size_t size_ );
	c_address find_signature( const std::vector< byte >& bytes ) const;
	void populate_interfaces( );
	c_address find_interface( const std::string& iface );
};