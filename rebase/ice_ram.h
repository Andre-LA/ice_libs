/*
ice_ram.h, Single-Header Cross-Platform C library to get RAM info!


================================== Full Overview ==================================

ice_ram.h is Single-Header Cross-Platform C library for working with RAM, It gives information about RAM usage!

To use it #define ICE_RAM_IMPL then #include "ice_ram.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation and include the library
#define ICE_RAM_IMPL
#include "ice_ram.h"

#include <stdio.h>

// Helper
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str)

int main(int argc, char** argv) {
    ice_ram_info info;

    // Fetch RAM info
    ice_ram_bool res = ice_ram_get_status(&info);

    // If function failed to fetch RAM info, Trace error then terminate the program
    if (res == ICE_RAM_FALSE) {
        trace("ice_ram_get_status", "ERROR: failed to get RAM info!");
        return -1;
    }
    
    // Print RAM info (free, used, total) in Bytes
    printf("%s %llu bytes\n%s %llu bytes\n%s %llu bytes\n",
            "Free RAM:", info.free,
            "Used RAM:", info.used,
            "Total RAM:", info.total);

    return 0;
}


=================================== Library API ===================================

// Typedef for free and used and total Bytes of RAM
typedef unsigned long long ice_ram_bytes;

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_ram_bool {
    ICE_RAM_FALSE = -1,
    ICE_RAM_TRUE = 0
} ice_ram_bool;

// RAM Information, Contains free and used and total RAM in Bytes
typedef struct ice_ram_info {
    ice_ram_bytes free;
    ice_ram_bytes used;
    ice_ram_bytes total;
} ice_ram_info;

// Retrives info about RAM (free, used, total) in Bytes and stores information into ice_ram_info struct by pointing to, Returns ICE_RAM_TRUE on success or ICE_RAM_FALSE on failure
ice_ram_bool ice_ram_get_status(ice_ram_info* info);


================================== Linking Flags ==================================

1. Microsoft Windows    =>  -lkernel32
2. BlackBerry 10        =>  -lbb

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragmas


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_ram.h in the code...
#define ICE_RAM_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_RAM_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_RAM_FASTCALL        // fastcall
#define ICE_RAM_STDCALL         // stdcall
#define ICE_RAM_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_RAM_MICROSOFT       // Microsoft platforms
#define ICE_RAM_APPLE           // Apple (MacOS, iOS, etc...)
#define ICE_RAM_BSD             // BSD (FreeBSD, OpenBSD, NetBSD, DragonFly BSD)
#define ICE_RAM_WEB             // Web (Emscripten)
#define ICE_RAM_TIZEN           // Tizen
#define ICE_RAM_BB10            // BlackBerry 10
#define ICE_RAM_LINUX           // Linux (This includes Android, Consoles, etc...)

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_RAM_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_RAM_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_RAM_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_RAM_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_RAM_EXTERN          // externs library functions
#define ICE_RAM_STATIC          // statics library functions

// NOTE: ICE_RAM_EXTERN and ICE_RAM_STATIC cannot be #defined together in the code...


============================== Implementation Resources ===========================

1. https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa965225(v=vs.85)
2. https://web.mit.edu/darwin/src/modules/xnu/osfmk/man/host_info.html
3. https://developer.mozilla.org/en-US/docs/Web/API/Performance/memory
4. https://docs.tizen.org/application/native/api/mobile/6.0/group__CAPI__SYSTEM__RUNTIME__INFO__MODULE.html
5. https://nodejs.org/api/os.html
6. https://developer.blackberry.com/native/reference/cascades/bb__memoryinfo.html
7. https://man7.org/linux/man-pages/man2/sysinfo.2.html


================================= Support ice_libs ================================

ice_ram.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_RAM_H
#define ICE_RAM_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_RAM_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_RAM_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_RAM_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_RAM_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_RAM_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_RAM_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_RAM_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_RAM_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_RAM_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_RAM_CDECL)
#  if defined(_MSC_VER)
#    define ICE_RAM_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_RAM_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_RAM_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_RAM_MICROSOFT) || defined(ICE_RAM_APPLE) || defined(ICE_RAM_WEB) || defined(ICE_RAM_TIZEN) || defined(ICE_RAM_BB10) || defined(ICE_RAM_LINUX))
#  define ICE_RAM_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
/* The implementation of BlackBerry 10 written in C++ instead of C, because his native API uses C++ :( */
#if defined(ICE_RAM_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_RAM_MICROSOFT 1
#  elif defined(__APPLE__) || defined(__DARWIN__) || defined(__MACH__)
#    define ICE_RAM_APPLE 1
#  elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#    define ICE_RAM_BSD 1
#  elif defined(__EMSCRIPTEN__)
#    define ICE_RAM_WEB 1
#  elif defined(__TIZEN__)
#    define ICE_RAM_TIZEN 1
#  elif defined(__BLACKBERRY10__) || defined(__BB10__)
#    define ICE_RAM_BB10 1
#    if !defined(__cplusplus)
#      error "BlackBerry 10 implementation cannot be used with C code, Only C++ :("
#    endif
#  elif defined(__linux__) || defined(__linux)
#    define ICE_RAM_LINUX 1
#  else
#    error "ice_ram.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_RAM_EXTERN) && defined(ICE_RAM_STATIC))
#  define ICE_RAM_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_RAM_EXTERN)
#  define ICE_RAM_APIDEF extern
#elif defined(ICE_RAM_STATIC)
#  define ICE_RAM_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_RAM_INLINE to enable inline functionality.
*/
#if defined(ICE_RAM_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_RAM_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_RAM_INLINEDEF inline
#  endif
#else
#  define ICE_RAM_INLINEDEF
#endif

/*
Allow to build DLL via ICE_RAM_DLLEXPORT or ICE_RAM_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_RAM_MICROSOFT)
#  if defined(ICE_RAM_DLLEXPORT)
#    define ICE_RAM_API __declspec(dllexport) ICE_RAM_INLINEDEF
#  elif defined(ICE_RAM_DLLIMPORT)
#    define ICE_RAM_API __declspec(dllimport) ICE_RAM_INLINEDEF
#  else
#    define ICE_RAM_API ICE_RAM_APIDEF ICE_RAM_INLINEDEF
#  endif
#else
#  define ICE_RAM_API ICE_RAM_APIDEF ICE_RAM_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Typedef for free and used and total Bytes of RAM */
typedef unsigned long long ice_ram_bytes;

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_ram_bool {
    ICE_RAM_FALSE = -1,
    ICE_RAM_TRUE = 0
} ice_ram_bool;

/* RAM Information, Contains free and used and total RAM in Bytes */
typedef struct ice_ram_info { ice_ram_bytes free, used, total; } ice_ram_info;

/* ============================== Functions ============================== */

/* Retrives info about RAM (free, used, total) in Bytes and stores information into ice_ram_info struct by pointing to, Returns ICE_RAM_TRUE on success or ICE_RAM_FALSE on failure */
ICE_RAM_API ice_ram_bool ICE_RAM_CALLCONV ice_ram_get_status(ice_ram_info* info);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_RAM_IMPL)

#if defined(ICE_RAM_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <sysinfoapi.h>
#  endif
#elif defined(ICE_RAM_APPLE)
#  include <mach/mach.h>
#  include <mach/mach_host.h>
#elif defined(ICE_RAM_BSD)
#  include <sys/types.h>
#  include <sys/sysctl.h>
#elif defined(ICE_RAM_WEB)
#  include <emscripten/emscripten.h>
#elif defined(ICE_RAM_TIZEN)
#  include <runtime_info.h>
#elif defined(ICE_RAM_BB10)
#  include <QtGlobal>
#  include <bb/MemoryInfo>
using namespace bb;
#elif defined(ICE_RAM_LINUX)
#  include <sys/sysinfo.h>
#endif

/* Retrives info about RAM (free, used, total) in bytes and stores information into ice_ram_info struct by pointing to, Returns ICE_RAM_TRUE on success or ICE_RAM_FALSE on failure */
ICE_RAM_API ice_ram_bool ICE_RAM_CALLCONV ice_ram_get_status(ice_ram_info* info) {
    ice_ram_bytes mem_free;
    ice_ram_bytes mem_used;
    ice_ram_bytes mem_total;

#if defined(ICE_RAM_MICROSOFT)
    MEMORYSTATUSEX status;
    int fetch_res;
    status.dwLength = sizeof(status);

    fetch_res = GlobalMemoryStatusEx(&status);

    if (fetch_res == 0) goto failure;

    mem_free = (ice_ram_bytes) status.ullAvailPhys;
    mem_used = (ice_ram_bytes) (status.ullTotalPhys - status.ullAvailPhys);
    mem_total = (ice_ram_bytes) status.ullTotalPhys;

#elif defined(ICE_RAM_APPLE)
    mach_port_t host_port = mach_host_self();
    mach_msg_type_number_t host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    vm_size_t pagesize;
    vm_statistics_data_t vm_stat;
    int fetch_res;
    
    fetch_res = host_page_size(host_port, &pagesize);
    if (fetch_res != 0) goto failure;

    fetch_res = host_statistics(host_port, HOST_VM_INFO, (host_info_t) &vm_stat, &host_size);
    if (fetch_res != 0) goto failure;
    
    mem_free = (ice_ram_bytes) vm_stat.free_count * pagesize;
    mem_used = (ice_ram_bytes) (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
    mem_total = (ice_ram_bytes) mem_used + mem_free;
    
#elif defined(ICE_RAM_BSD)
    const char* sysctl_names[5] = {
        "hw.pagesize",
        "hw.physmem",
        "vm.stats.vm.v_inactive_count",
        "vm.stats.vm.v_cache_count",
        "vm.stats.vm.v_free_count"
    };
    
    ice_ram_bytes sysctl_res[5] = { 0, 0, 0, 0, 0 };
    
    unsigned sysctls_done = 0;
    int i;
    
    for (i = 0; i < 5; i++) {
        int res = sysctlbyname(sysctl_names[i], &sysctl_res[i], 0, 0, 0);
        
        if (res != 0) {
            goto failure;
        } else {
            sysctls_done++;
        }
    }
    
    mem_total = (ice_ram_bytes) sysctl_res[1];
    mem_free = (ice_ram_bytes) (sysctl_res[2] + sysctl_res[3] + sysctl_res[4]) * sysctl_res[0];
    mem_used = (ice_ram_bytes) (mem_total - mem_free);

#elif defined(ICE_RAM_WEB)
    mem_free = (ice_ram_bytes) EM_ASM_INT({
        if (!require) {
            return ((window.navigator.deviceMemory || 0) * 1024 * 1024 * 1024) - (window.performance.memory.usedJSHeapSize || 0);
        } else {
            return (require("os").freemem() || 0);
        }
    });

    mem_used = (ice_ram_bytes) EM_ASM_INT({
        return (window.performance.memory.usedJSHeapSize || 0);
    });

    mem_total = (ice_ram_bytes) EM_ASM_INT({
        if (!require) {
            return (window.navigator.deviceMemory || 0) * 1024 * 1024 * 1024;
        } else {
            return (require("os").totalmem() || 0);
        }
    });

#elif defined(ICE_RAM_TIZEN)
    runtime_memory_info_s inf;
    int fetch_res = runtime_info_get_system_memory_info(&inf);

    if (fetch_res != 0) goto failure;

    mem_free = (ice_ram_bytes) (inf.free * 1024);
    mem_used = (ice_ram_bytes) (inf.used * 1024);
    mem_total = (ice_ram_bytes) (inf.total * 1024);
    
#elif defined(ICE_RAM_BB10)
    bb::MemoryInfo info;
    
    mem_free = (ice_ram_bytes) info.availableDeviceMemory();
    mem_used = (ice_ram_bytes) info.memoryUsedByCurrentProcess();
    mem_total = (ice_ram_bytes) info.totalDeviceMemory();
    
    delete info;
    
#elif defined(ICE_RAM_LINUX)
    struct sysinfo si;
    int fetch_res = sysinfo(&si);

   if (fetch_res != 0) goto failure;

    mem_free = (ice_ram_bytes) si.freeram;
    mem_used = (ice_ram_bytes) si.totalram - si.freeram;
    mem_total = (ice_ram_bytes) si.totalram;
#endif

   info->free = mem_free;
   info->used = mem_used;
   info->total = mem_total;

   return ICE_RAM_TRUE;

failure:
   info->free = 0;
   info->used = 0;
   info->total = 0;

   return ICE_RAM_FALSE;
}

#endif  /* ICE_RAM_IMPL */
#endif  /* ICE_RAM_H */

/*
ice_ram.h is dual-licensed, Choose the one you prefer!

------------------------------------------------------------------------
LICENSE A - PUBLIC DOMAIN LICENSE
------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

------------------------------------------------------------------------
LICENSE B - MIT LICENSE
------------------------------------------------------------------------
Copyright (c) 2021 - <Present> Rabia Alhaffar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
