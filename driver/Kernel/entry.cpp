#include "imports.h"
#include "functions.h"

auto driver_entry() -> const NTSTATUS
{

    auto win32k = utils::get_kernel_module( "win32k.sys" );
    if (!win32k) {
        dbg( "win32k not found!" );
        return STATUS_FAILED_DRIVER_ENTRY;
    }

    globals::hook_address = win32k + 0x664E8; // change this offset to whatever you want to hook to

    globals::hook_pointer = *reinterpret_cast< uintptr_t* >( globals::hook_address );
    *reinterpret_cast< uintptr_t* >( globals::hook_address ) = reinterpret_cast< uintptr_t >( &hooked_function );


    return STATUS_SUCCESS;
}