cmake_minimum_required(VERSION 3.24)
project(FocusQQWindow2 LANGUAGES CXX)


add_library(FocusQQWindow2 SHARED
    dllmain.cpp
    pch.cpp
)

target_compile_features(FocusQQWindow2
    PUBLIC
        cxx_std_20
)

target_precompile_headers(FocusQQWindow2
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
)

target_compile_definitions(FocusQQWindow2
    PUBLIC
        FOCUSQQWINDOW2_EXPORTS
        _WINDOWS
        _USRDLL
        UNICODE
        _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},X86>:WIN32>
)

target_compile_options(FocusQQWindow2
    PUBLIC
        /W3
)

