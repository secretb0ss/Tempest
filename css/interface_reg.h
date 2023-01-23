#pragma once

namespace valve {
	class interface_reg {
		typedef void* ( *instantiate_interface_fn )( );
	public:
		instantiate_interface_fn create_fn;
		const char* name;
		interface_reg* next;
	};
}