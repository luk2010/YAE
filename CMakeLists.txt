cmake_minimum_required(VERSION 3.12)

include(cmake/languages.cmake)
include(cmake/policies.cmake)

# Sets the binary directories.
set(YAE_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Sets the YAE include directory.
set(YAE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

project(YAE LANGUAGES ${YAE_PROJECT_LANGUAGES})

file(GLOB YAE_SOURCES_COMMON src/YAE/*.cpp)
file(GLOB YAE_HEADERS_COMMON src/YAE/*.h)

add_library(YAE SHARED ${YAE_SOURCES_COMMON} ${YAE_HEADERS_COMMON})
target_include_directories(YAE PRIVATE src)

if (APPLE) 

    find_library(YAE_LIB_COCOA Cocoa REQUIRED)
    find_library(YAE_LIB_CF CoreFoundation REQUIRED)
    find_library(YAE_LIB_CORETEXT CoreText REQUIRED)
    find_library(YAE_LIB_COREGRAPHICS CoreGraphics REQUIRED)
    target_link_libraries(YAE PRIVATE ${YAE_LIB_COCOA} ${YAE_LIB_CF} ${YAE_LIB_CORETEXT} ${YAE_LIB_COREGRAPHICS})

    if (NOT IOS)

        file(GLOB YAE_SOURCES_APPLE "src/YAE/APPLE/*.mm")
        file(GLOB YAE_HEADERS_APPLE "src/YAE/APPLE/*.h")

        target_sources(YAE PRIVATE ${YAE_SOURCES_APPLE} ${YAE_HEADERS_APPLE})

        message(STATUS "YAE: Added OSX support.")
        set(YAE_LIB_OSX 1)

    else () 

        file(GLOB YAE_SOURCES_IOS "src/YAE/IOS/*.mm")
        file(GLOB YAE_HEADERS_IOS "src/YAE/IOS/*.h")

        target_sources(YAE PRIVATE ${YAE_SOURCES_IOS} ${YAE_HEADERS_IOS})

        message(STATUS "YAE: Added IOS support.")
        set(YAE_LIB_IOS 1)

    endif ()

elseif (WIN32) 

    file(GLOB YAE_SOURCES_WIN "src/YAE/WIN/*.cpp")
    file(GLOB YAE_HEADERS_WIN "src/YAE/WIN/*.h")

    target_sources(YAE PRIVATE ${YAE_SOURCES_WIN} ${YAE_HEADERS_WIN})

    message(STATUS "YAE: Added WIN support.")
    set(YAE_LIB_WIN 1)

elseif (UNIX)

    find_package(X11 REQUIRED)

    file(GLOB YAE_SOURCES_X11 "src/YAE/X11/*.cpp")
    file(GLOB YAE_HEADERS_X11 "src/YAE/X11/*.h")

    target_sources(YAE PRIVATE ${YAE_SOURCES_X11} ${YAE_HEADERS_X11})
    target_include_directories(YAE PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(YAE PRIVATE ${X11_LIBRARIES})

    message(STATUS "YAE: Selected GUI Platform X11.")
    set(YAE_LIB_X11 1)

else () 

    message(FATAL_ERROR "YAE: Platform not supported for now.")
    
endif ()

# Configures the platform header.
configure_file(cmake/config.h.in configure.h)

# Adds the header file to the target.
target_sources(YAE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

# Adds the header to every upcoming targets.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS YAE DESTINATION ${YAE_BIN_DIR})

add_subdirectory(tutorials/HelloWorld)
