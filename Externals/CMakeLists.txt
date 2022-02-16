add_subdirectory(LuaJIT-proj)
add_subdirectory(luabind)
add_subdirectory(cximage)
add_subdirectory(GameSpy)
add_subdirectory(OPCODE)
add_subdirectory(ode)
#add_subdirectory(NVTT)

if (NINTENDO_SWITCH)
    add_subdirectory(glad)
endif()

if (MEMORY_ALLOCATOR STREQUAL "mimalloc")
    set(MI_BUILD_TESTS   OFF)
    set(MI_BUILD_DYNAMIC OFF)
    add_subdirectory(mimalloc)
    set_target_properties(mimalloc-static PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif()
