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

if (APPLE) 

    find_library(YAE_LIB_COCOA Cocoa)
    find_library(YAE_LIB_CF CoreFoundation)
    target_link_libraries(YAE PRIVATE ${YAE_LIB_COCOA} ${YAE_LIB_CF})

    if (NOT IOS)

        file(GLOB YAE_SOURCES_APPLE "src/YAE/APPLE/*.mm")
        file(GLOB YAE_HEADERS_APPLE "src/YAE/APPLE/*.h")

        target_sources(YAE PRIVATE ${YAE_SOURCES_APPLE} ${YAE_HEADERS_APPLE})

        message(STATUS "YAE: Added OSX support.")

    else () 

        file(GLOB YAE_SOURCES_IOS "src/YAE/IOS/*.mm")
        file(GLOB YAE_HEADERS_IOS "src/YAE/IOS/*.h")

        target_sources(YAE PRIVATE ${YAE_SOURCES_IOS} ${YAE_HEADERS_IOS})

        message(STATUS "YAE: Added IOS support.")

    endif ()

elseif (WIN32) 

    file(GLOB YAE_SOURCES_WIN "src/YAE/WIN/*.cpp")
    file(GLOB YAE_HEADERS_WIN "src/YAE/WIN/*.h")

    target_sources(YAE PRIVATE ${YAE_SOURCES_WIN} ${YAE_HEADERS_WIN})

    message(STATUS "YAE: Added WIN support.")

else () 

    message(FATAL "YAE: Platform not supported for now.")
    
endif ()

install(TARGETS YAE DESTINATION ${YAE_BIN_DIR})
