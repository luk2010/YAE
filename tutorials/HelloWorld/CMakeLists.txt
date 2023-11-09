
add_executable(
    HelloWorld
        MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(
    HelloWorld
    PRIVATE 
        YAE 
)

target_include_directories(
    HelloWorld 
    PRIVATE 
        ${YAE_INCLUDE_DIR}
)

install(
    TARGETS
        HelloWorld
    DESTINATION 
        ${YAE_BIN_DIR}
)
