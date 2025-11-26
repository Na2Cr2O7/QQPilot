cmake_minimum_required(VERSION 3.24)
project(uploadFile LANGUAGES CXX)


add_library(uploadFile SHARED
    dllmain.cpp
    pch.cpp
)

target_compile_features(uploadFile
    PUBLIC
        cxx_std_20
)

target_precompile_headers(uploadFile
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
)

target_compile_definitions(uploadFile
    PUBLIC
        UPLOADFILE_EXPORTS
        _WINDOWS
        _USRDLL
        UNICODE
        _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},X86>:WIN32>
)

target_compile_options(uploadFile
    PUBLIC
        /W3
)

