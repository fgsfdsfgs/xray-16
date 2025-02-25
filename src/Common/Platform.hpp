#pragma once

#if defined(_WIN32)
#   define XR_PLATFORM_WINDOWS
#   define _XRAY_PLATFORM_MARKER "Windows"
#elif defined(__SWITCH__)
#   define XR_PLATFORM_SWITCH
#   define _XRAY_PLATFORM_MARKER "Switch"
#elif defined(__linux__)
#   define XR_PLATFORM_LINUX
#   define _XRAY_PLATFORM_MARKER "Linux"
#elif defined(__FreeBSD__)
#   define XR_PLATFORM_FREEBSD
#   define _XRAY_PLATFORM_MARKER "FreeBSD"
#else
#   error Unsupported platform
#endif

#if defined(_M_IX86) || defined(__i386__) || defined(_X86_)
#   define XR_ARCHITECTURE_X86
#   define _XRAY_ARCHITECTURE_MARKER "32-bit"
#elif defined(_M_X64) || defined(__amd64__) || defined(__x86_64__)
#   define XR_ARCHITECTURE_X64
#   define _XRAY_ARCHITECTURE_MARKER "64-bit"
#elif defined(_M_ARM) || defined(__arm__)
#   define XR_ARCHITECTURE_ARM
#   define _XRAY_ARCHITECTURE_MARKER "ARM 32-bit"
#elif defined (_M_ARM64) || defined(__aarch64__)
#   define XR_ARCHITECTURE_ARM64
#   define _XRAY_ARCHITECTURE_MARKER "ARM 64-bit"
#elif defined (__e2k__)
#   define XR_ARCHITECTURE_E2K
#   define _XRAY_ARCHITECTURE_MARKER "E2K"
#else
#   error Unsupported architecture
#endif

#if defined(_MSC_VER)
#define XR_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#define XR_COMPILER_GCC __GNUC__
#else
#error Unsupported compiler
#endif
#include "Common/Compiler.inl"

#if defined(XR_PLATFORM_WINDOWS)
#include "Common/PlatformWindows.inl"
#elif defined(XR_PLATFORM_LINUX) || defined(XR_PLATFORM_SWITCH)
#include "Common/PlatformLinux.inl"
#elif defined(XR_PLATFORM_FREEBSD)
#include "Common/PlatformBSD.inl"
#else
#error Provide Platform.inl file for your platform
#endif

#ifdef XRAY_STATIC_BUILD
#   define _XRAY_STATIC_BUILD_MARKER "static"
#else
#   define _XRAY_STATIC_BUILD_MARKER "shared"
#endif

#ifdef MASTER_GOLD
#   define _XRAY_MASTER_GOLD_MARKER " Master Gold"
#else
#   define _XRAY_MASTER_GOLD_MARKER
#endif

#if defined(NDEBUG)
#   define _XRAY_CONFIGURATION_MARKER "Release"
#elif defined(MIXED)
#   define _XRAY_CONFIGURATION_MARKER "Mixed"
#elif defined(DEBUG)
#   define _XRAY_CONFIGURATION_MARKER "Debug"
#else
#   error Unknown configuration
#endif

#define XRAY_BUILD_CONFIGURATION _XRAY_CONFIGURATION_MARKER _XRAY_MASTER_GOLD_MARKER
#define XRAY_BUILD_CONFIGURATION2 _XRAY_PLATFORM_MARKER " " _XRAY_ARCHITECTURE_MARKER ", " _XRAY_STATIC_BUILD_MARKER
