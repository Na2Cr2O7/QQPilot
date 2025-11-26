cmake_minimum_required(VERSION 3.24)
project(Vimage LANGUAGES CXX)


add_library(Vimage SHARED
    dllmain.cpp
    pch.cpp
)

target_compile_features(Vimage
    PUBLIC
        cxx_std_20
)

target_precompile_headers(Vimage
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
)

target_compile_definitions(Vimage
    PUBLIC
        VIMAGE_EXPORTS
        _WINDOWS
        _USRDLL
        UNICODE
        _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},X86>:WIN32>
)

target_compile_options(Vimage
    PUBLIC
        /W3
)

