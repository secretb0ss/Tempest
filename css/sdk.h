#pragma once

#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <Psapi.h>
#include <unordered_map>

// disable warnings for dependencies, im not going to fix
// their libraries.
#pragma warning( push, 0 )
#include "dependencies/xxhash/xxhash.h"
#pragma warning( pop )

#include "console.h"
#include "address.h"
#include "signature.h"
#include "module.h"

#include "hashing.h"

#include "modules.h"
#include "css.h"