cmake_minimum_required(VERSION 3.24)
project(wxInstall LANGUAGES CXX)


add_executable(wxInstall WIN32
    ui.cpp
    wxInstall.cpp
)

target_compile_features(wxInstall
    PUBLIC
        cxx_std_20
)

target_include_directories(wxInstall
    PUBLIC
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},x64>:${WXWIN}/include>
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},x64>:${WXWIN}/include/msvc>
)

target_compile_definitions(wxInstall
    PUBLIC
        _WINDOWS
        UNICODE
        _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

target_link_directories(wxInstall
    PUBLIC
        $<$<STREQUAL:${CMAKE_CXX_COMPILER_ARCHITECTURE_ID},x64>:${WXWIN}/lib/vc_x64_lib>
)

target_compile_options(wxInstall
    PUBLIC
        /W3
)

