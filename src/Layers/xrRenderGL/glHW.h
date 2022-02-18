#pragma once

#include "Layers/xrRender/HWCaps.h"
#include "xrCore/ModuleLookup.hpp"
#include "SDL.h"
#include "SDL_syswm.h"

#ifdef USE_GLAD
#define GLEXT_SUPPORTED(x) (GLAD_ ## x)
#else
#define GLEXT_SUPPORTED(x) (glewIsSupported(#x))
#endif

class CHW
    : public pureAppActivate,
      public pureAppDeactivate
{
public:
    CHW();
    ~CHW();

    void CreateDevice(SDL_Window* sdlWnd);
    void DestroyDevice();

    void Reset();

    void SetPrimaryAttributes();

    IRender::RenderContext GetCurrentContext() const;
    int  MakeContextCurrent(IRender::RenderContext context) const;

    static std::pair<u32, u32> GetSurfaceSize();
    DeviceState GetDeviceState() const;

public:
    void BeginScene();
    void EndScene();
    void Present();

public:
    void OnAppActivate() override;
    void OnAppDeactivate() override;

private:
    void UpdateViews();
    bool ThisInstanceIsGlobal() const;

public:
    void BeginPixEvent(pcstr name) const;
    void EndPixEvent() const;

public:
    CHWCaps Caps;

    u32 BackBufferCount{};
    u32 CurrentBackBuffer{};
    
    GLuint pPP{};
    GLuint pFB{};

    SDL_Window* m_window{};
    SDL_Window* m_helper_window{};

    SDL_GLContext m_context{};
    SDL_GLContext m_helper_context{};

    pcstr AdapterName;
    pcstr OpenGLVersionString;
    pcstr ShadingVersion;
    std::pair<GLint, GLint> OpenGLVersion;
    bool ShaderBinarySupported;
    bool ComputeShadersSupported;
};

extern ECORE_API CHW HW;
