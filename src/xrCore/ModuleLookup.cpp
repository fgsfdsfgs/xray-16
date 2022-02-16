#include "stdafx.h"

#ifdef XR_PLATFORM_SWITCH

#include <solder.h>

#define LoadObject(x) solder_dlopen((x), SOLDER_LOCAL | SOLDER_NOW)
#define UnloadObject(h) solder_dlclose((h))
#define LoadFunction(h, f) solder_dlsym((h), (f))
#define GetLoadError() solder_dlerror()

#else

#include <SDL_loadso.h>

#define LoadObject(x) SDL_LoadObject(x)
#define UnloadObject(h) SDL_UnloadObject(h)
#define LoadFunction(h, f) SDL_LoadFunction(h, f)
#define GetLoadError() SDL_GetError()

#endif

#include "ModuleLookup.hpp"

namespace XRay
{
ModuleHandle::ModuleHandle(const bool dontUnload) : handle(nullptr), dontUnload(dontUnload) {}

ModuleHandle::ModuleHandle(pcstr moduleName, bool dontUnload /*= false*/) : handle(nullptr), dontUnload(dontUnload)
{
    this->Open(moduleName);
}

ModuleHandle::~ModuleHandle()
{
    Close();
}

void* ModuleHandle::Open(pcstr moduleName)
{
    if (IsLoaded())
        Close();

    Log("Loading module:", moduleName);

    xr_string buf(moduleName);

#ifdef XR_PLATFORM_WINDOWS
    buf += ".dll";
#elif defined(XR_PLATFORM_LINUX) || defined(XR_PLATFORM_FREEBSD) || defined(XR_PLATFORM_SWITCH)
    buf += ".so";
#else
#error add your platform-specific extension here
#endif

    handle = LoadObject(buf.c_str());

    if (!handle)
    {
        Log("! Failed to load module:", moduleName);
        Log("!", GetLoadError());
    }

    return handle;
}

void ModuleHandle::Close()
{
    if (dontUnload)
        return;

    UnloadObject(handle);
    handle = nullptr;
}

bool ModuleHandle::IsLoaded() const
{
    return handle != nullptr;
}

void* ModuleHandle::operator()() const
{
    return handle;
}

void* ModuleHandle::GetProcAddress(pcstr procName) const
{
    const auto proc = LoadFunction(handle, procName);

    if (!proc)
    {
        Log("! Failed to load function from module:", procName);
        Log("!", GetLoadError());
    }

    return proc;
}
} // namespace XRay
