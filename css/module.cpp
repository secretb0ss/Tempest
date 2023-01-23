#include "sdk.h"

c_module::c_module( const std::string& name_, const c_address base_address_, const size_t size_ ) : base_address( base_address_ ), name( name_ ), size( size_ ) {
	auto hashed_name = hashing::get_hash( this->name );

	// only populate interfaces of the game dlls we need
	if ( hashed_name == hashing::get_hash( "client.dll" ) ||
		hashed_name == hashing::get_hash( "engine.dll" ) )
		this->populate_interfaces( );
}

c_address c_module::find_signature( const std::vector< byte >& bytes ) const {
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

void c_module::populate_interfaces( ) {
	// s_pInterfaceRegs
	auto cur_interface = this->find_signature( { 0x8B,0x35,0xAE,0xAE,0xAE,0xAE,0x57,0x85,0xF6,0x74,0x38 } ).add( 0x2 ).dereference< interface_reg*, 2 >( );
	
	while ( cur_interface ) {
		interface_map.insert( { hashing::get_hash( cur_interface->name ), { cur_interface->name, reinterpret_cast< uintptr_t >( cur_interface->create_fn( ) ) } } );
		cur_interface = cur_interface->next;
	}

	if ( interface_map.empty( ) )
		throw std::runtime_error( "failed to fill interface map" );
}

c_address c_module::find_interface( const std::string& iface ) {
	const auto it = interface_map.find( hashing::get_hash( iface ) );

	if ( it == interface_map.end( ) )
		throw std::runtime_error( std::format( "failed to find module {}", iface ) );

	return it->second.second;
}