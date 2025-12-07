cmake_minimum_required(VERSION 3.24)
project(InputEvent LANGUAGES CXX)


add_library(InputEvent SHARED
    dllmain.cpp
    keybdevent.cpp
    mouseEvent.cpp
    pch.cpp
)

target_compile_features(InputEvent
    PUBLIC
        cxx_std_20
)

target_precompile_headers(InputEvent
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
)

target_compile_definitions(InputEvent
    PUBLIC
        INPUTEVENT_EXPORTS
        _WINDOWS
        _USRDLL
        UNICODE
        _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},X86>:WIN32>
)

target_compile_options(InputEvent
    PUBLIC
        /W3
)

