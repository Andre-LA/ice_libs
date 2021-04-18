// Written by Rabia Alhaffar in 18/April/2021
// ice_ram.h
// Single-Header Cross-Platform C library to get free and total RAM!
// Updated: 19/April/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ram.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_ram is Single-Header Cross-Platform C library to get free and total RAM!

Works on:

1. Windows and Xbox platforms
2. OSX
3. iOS
4. Linux (Including BeOS, Haiku, Android)
5. Emscripten
6. PSP

[2] IMPLEMENTATION:
Windows             -> GlobalMemoryStatusEx
Apple               -> host_statistics (mach.h and mach_host.h)
Unix                -> sysinfo
Emscripten          -> os module (Node.js), window.performance.memory + navigator.deviceMemory (Web)

[3] USAGE:
Define ICE_RAM_IMPL Then include ice_ram.h in your C/C++ code!

*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_ram
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_ram by possibly one of following things:
//
// 1. Test ice_ram on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

#ifndef ICE_RAM_H
#define ICE_RAM_H

// Define C interface for Windows libraries! ;)
#ifndef CINTERFACE
#  define CINTERFACE
#endif

// Allow to use calling conventions if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_RAM_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_RAM_CALLCONV_FASTCALL)
#    define ICE_RAM_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_RAM_CALLCONV_STDCALL)
#    define ICE_RAM_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_RAM_CALLCONV_CDECL)
#    define ICE_RAM_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_RAM_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_RAM_CALLCONV_VECTORCALL)
#    define ICE_RAM_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_RAM_CALLCONV_FASTCALL)
#    define ICE_RAM_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_RAM_CALLCONV_STDCALL)
#    define ICE_RAM_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_RAM_CALLCONV_CDECL)
#    define ICE_RAM_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_RAM_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_RAM_CALLCONV_VECTORCALL)
#    define ICE_RAM_CALLCONV __vectorcall
#  elif defined(ICE_RAM_CALLCONV_FASTCALL)
#    define ICE_RAM_CALLCONV __fastcall
#  elif defined(ICE_RAM_CALLCONV_STDCALL)
#    define ICE_RAM_CALLCONV __stdcall
#  elif defined(ICE_RAM_CALLCONV_CDECL)
#    define ICE_RAM_CALLCONV __cdecl
#  else
#    define ICE_RAM_CALLCONV
#  endif
#else
#  define ICE_RAM_CALLCONV
#endif

// Allow to use them as extern functions if desired!
#if defined(ICE_RAM_EXTERN)
#  define ICE_RAM_EXTERNDEF extern
#else
#  define ICE_RAM_EXTERNDEF
#endif

#if !(defined(ICE_RAM_MICROSOFT) || defined(ICE_RAM_UNIX) || defined(ICE_RAM_APPLE) || defined(ICE_RAM_WEB) || defined(ICE_RAM_PSP))
#  define ICE_RAM_PLATFORM_AUTODETECTED
#endif

// ice_ram autodetection system (Huge but still worthy...)
#if defined(ICE_RAM_PLATFORM_AUTODETECTED)
#  if defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)
#    define ICE_RAM_UNIX
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    define ICE_RAM_APPLE
#  elif defined(__EMSCRIPTEN__) || defined(__EMSCRIPTEN) || defined(EMSCRIPTEN)
#    define ICE_RAM_WEB
#  elif (defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)) || (defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU))
#    define ICE_RAM_UNIX
#  elif defined(__linux__) || defined(__LINUX__) || defined(LINUX) || defined(__LINUX) || defined(__linux) || defined(linux) && !(defined(__ANDROID__) || defined(ANDROID) || defined(__ANDROID) || defined(__android))
#    define ICE_RAM_UNIX
#  elif defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox)
#    define ICE_RAM_MICROSOFT
#  elif defined(PSP) || defined(__PSP__) || defined(__psp__) || defined(__PSP) || defined(_PSP)
#    define ICE_RAM_PSP
#  endif
#endif

// Allow to build DLL via ICE_RAM_DLLEXPORT or ICE_RAM_DLLIMPORT if desired!
// Else, Just define API as static inlined C code!
#if defined(ICE_RAM_MICROSOFT)
#  if defined(ICE_RAM_DLLEXPORT)
#    define ICE_RAM_API ICE_RAM_EXTERNDEF __declspec(dllexport) inline
#  elif defined(ICE_RAM_DLLIMPORT)
#    define ICE_RAM_API ICE_RAM_EXTERNDEF __declspec(dllimport) inline
#  else
#    define ICE_RAM_API ICE_RAM_EXTERNDEF static inline
#  endif
#else
#  define ICE_RAM_API ICE_RAM_EXTERNDEF static inline
#endif

//#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ram API
///////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned long long int ice_ram_bytes;

ICE_RAM_API  ice_ram_bytes  ICE_RAM_CALLCONV  ice_ram_total(void);           // Returns total memory (RAM) device has, In bytes.
ICE_RAM_API  ice_ram_bytes  ICE_RAM_CALLCONV  ice_ram_free(void);            // Returns available/free memory (RAM) device has, In bytes.

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ram IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_RAM_IMPL)

#if defined(ICE_RAM_WEB)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_RAM_WEB IMPLEMENTATION    (Both Node.js and Web)
///////////////////////////////////////////////////////////////////////////////////////////
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

// Returns total memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_total(void) {
    return (ice_ram_bytes) EM_ASM_INT({
       if (!require) {
         return (window.navigator.deviceMemory || 0) * 1024 * 1024 * 1024;
       } else {
         return require("os").totalmem();
       }
    });
}

// Returns available/free memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_free(void) {
    return (ice_ram_bytes) EM_ASM_INT({
       if (!require) {
         return ((window.navigator.deviceMemory || 0) * 1024 * 1024 * 1024) - (window.performance.memory.usedJSHeapSize || 0);
       } else {
         return require("os").freemem();
       }
    });
}

#elif defined(ICE_RAM_MICROSOFT)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_RAM_MICROSOFT IMPLEMENTATION     (Microsoft platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

MEMORYSTATUSEX statex;

// Returns total memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_total(void) {
    statex.dwLength = sizeof(statex);
    
    if (GlobalMemoryStatusEx(&statex)) {
        return (ice_ram_bytes) statex.ullTotalPhys;
    }
    
    return 0;
}

// Returns available/free memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_free(void) {
    statex.dwLength = sizeof(statex);
    
    if (GlobalMemoryStatusEx(&statex)) {
        return (ice_ram_bytes) statex.ullAvailPhys;
    }
    
    return 0;
}

#elif defined(ICE_RAM_APPLE)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_RAM_APPLE IMPLEMENTATION     (Apple platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <mach/mach.h>
#include <mach/mach_host.h>

mach_port_t host_port;
mach_msg_type_number_t host_size;
vm_size_t pagesize;
vm_statistics_data_t vm_stat;

// Returns total memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_total(void) {
    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);

    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) {
        return 0;
    }

    // Stats in bytes
    natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
    natural_t mem_free = vm_stat.free_count * pagesize;
    natural_t mem_total = mem_used + mem_free;
    
    return (ice_ram_bytes) mem_total;
    
    //return (ice_ram_bytes) [NSProcessInfo processInfo].physicalMemory;
}

// Returns available/free memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_free(void) {
    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);

    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t) &vm_stat, &host_size) != KERN_SUCCESS) {
        return 0;
    }

    // Stats in bytes
    natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;
    natural_t mem_free = vm_stat.free_count * pagesize;
    natural_t mem_total = mem_used + mem_free;
    
    return (ice_ram_bytes) mem_free;
}

#elif defined(ICE_RAM_UNIX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_RAM_UNIX IMPLEMENTATION     (Android, Linux, BSD, Haiku, BeOS, etc...)
///////////////////////////////////////////////////////////////////////////////////////////
#include <sys/sysinfo.h>

struct sysinfo si;

// Returns total memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_total(void) {
    sysinfo(&si);
    return (ice_ram_bytes) si.totalram;
}

// Returns available/free memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_free(void) {
    sysinfo(&si);
    return (ice_ram_bytes) si.freeram;
}

#elif defined(ICE_RAM_PSP)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_RAM_PSP IMPLEMENTATION     (Sony PlayStation Portable)
///////////////////////////////////////////////////////////////////////////////////////////
#include <pspsysmem.h>

// Returns total memory (RAM) device has, In bytes.
// NOTE: Fallback to 64 MB cause most PSPs not PSP-1000, If someone have way to detect PSP-1000 tell me...
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_total(void) {
    return (64 * 1024 * 1024);
}

// Returns available/free memory (RAM) device has, In bytes.
ICE_RAM_API ice_ram_bytes ICE_RAM_CALLCONV ice_ram_free(void) {
    return (ice_ram_bytes) sceKernelTotalFreeMemSize(); 
}

#endif

#endif  // ICE_RAM_IMPL
#endif  // ICE_RAM_H
