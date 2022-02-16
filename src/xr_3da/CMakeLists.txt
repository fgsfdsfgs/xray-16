project(xr_3da)

set(SRC_FILES
    "AccessibilityShortcuts.hpp"
    "entry_point.cpp"
    "resource.h"
    "stdafx.h"
    "stdafx.cpp"
)

group_sources(SRC_FILES)

if (NINTENDO_SWITCH)
    # add mimalloc's malloc replacer object
    set(SRC_FILES "" ${SRC_FILES})
    # link everything to the main executable since they're all static libs
    set(PLATFORM_LIBS
        -rdynamic
        -L"$ENV{DEVKITPRO}/libnx/lib"
        -L"$ENV{DEVKITPRO}/portlibs/switch/lib"
        -ftls-model=local-exec
        -Wl,--exclude-libs=libglapi.a -Wl,--exclude-libs=libdrm_nouveau.a
        -Wl,--unresolved-symbols=ignore-in-shared-libs
        -Wl,--whole-archive
        $<$<STREQUAL:${MEMORY_ALLOCATOR},mimalloc>:mimalloc-static>
        -ltheora -lvorbisfile -lvorbis -logg -lopenal -lpng -ljpeg -llzo2 -lz -lm -lSDL2
        -Wl,--no-whole-archive
        -lEGL -lglapi -ldrm_nouveau
        -lsolderd -lnx -lstdc++
    )
    set(PLATFORM_INCLUDE_DIRS "$ENV{DEVKITPRO}/portlibs/switch/include")
else()
    set(PLATFORM_LIBS )
    set(PLATFORM_INCLUDE_DIRS )
endif()

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${SDL_INCLUDE_DIRS}
    ${PLATFORM_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    xrCore
    xrAPI
    xrEngine
    ${PLATFORM_LIBS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

if (NOT CMAKE_CROSSCOMPILING)
    install(TARGETS ${PROJECT_NAME} RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    )
endif()
