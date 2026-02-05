cmake_minimum_required(VERSION 3.24)
project(ScaleToINI LANGUAGES CXX)


add_executable(ScaleToINI
    ScaleToINI.cpp
)

target_compile_definitions(ScaleToINI
    PUBLIC
        _CONSOLE
        UNICODE
        _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},X86>:WIN32>
)

target_compile_options(ScaleToINI
    PUBLIC
        /W3
)

