cmake_minimum_required (VERSION 3.1)
project (Phantom)


set (CMAKE_C_STANDARD 17)
set (CMAKE_CXX_STANDARD 17)
#set (CMAKE_VERBOSE_MAKEFILE on)


include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/PhantomEngine")
include_directories("${PROJECT_SOURCE_DIR}/PhantomEngine/Common")


# Setup OS
if(${UNIX})
    if(${APPLE})
        SET(BUILD_OS "Apple")
        add_compile_definitions(APPLE)
    else()
        SET(BUILD_OS "Linux")
        add_compile_definitions(LINUX)
    endif()
else()
    SET(BUILD_OS "Windows")
    add_definitions(-DWINDOWS)
endif()

# Build all libraries
add_subdirectory(PhantomEngine)
add_subdirectory(Application/${BUILD_OS})
# add_subdirectory(Tests/RTTI)


# Link according to OS
set(ENGINE_LIBS Application Render Math IO Common)
add_executable(${PROJECT_NAME} Main.cpp)
IF(BUILD_OS STREQUAL "Windows")
    set(GRAPHICS_API_LIBS d3d11.lib d3dcompiler.lib)
ENDIF()

target_link_libraries(${PROJECT_NAME} ${ENGINE_LIBS} ${GRAPHICS_API_LIBS})


# Display environment
message("LIB : " ${LIB})
message("CMAKE_SOURCE_DIR : " ${CMAKE_SOURCE_DIR})
message("CMAKE_INCLUDE_PATH : " ${CMAKE_INCLUDE_PATH})
message("CMAKE_SYSTEM_INCLUDE_PATH : " ${CMAKE_SYSTEM_INCLUDE_PATH})
message("CMAKE_C_INCLUDE_WHAT_YOU_USE : " ${CMAKE_C_INCLUDE_WHAT_YOU_USE})
message("CMAKE_CXX_INCLUDE_WHAT_YOU_USE : " ${CMAKE_CXX_INCLUDE_WHAT_YOU_USE})
message("CMAKE_C_STANDARD_INCLUDE_DIRECTORIES : " ${CMAKE_C_STANDARD_INCLUDE_DIRECTORIES})
message("CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES : " ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
message("CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES : " ${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES})
message("CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES : " ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
message("CMAKE_DEF_IMPLICIT_INCLUDE_DIRECTORIES : " ${CMAKE_DEF_IMPLICIT_INCLUDE_DIRECTORIES})

message("CMAKE_LIBRARY_PATH : " ${CMAKE_LIBRARY_PATH})
message("CMAKE_SYSTEM_LIBRARY_PATH : " ${CMAKE_SYSTEM_LIBRARY_PATH})
message("CMAKE_VS_SDK_LIBRARY_DIRECTORIES : " ${CMAKE_VS_SDK_LIBRARY_DIRECTORIES})
message("CMAKE_VS_SDK_LIBRARY_WINRT_DIRECTORIES : " ${CMAKE_VS_SDK_LIBRARY_WINRT_DIRECTORIES})
message("CMAKE_C_STANDARD_LIBRARIES : " ${CMAKE_C_STANDARD_LIBRARIES})
message("CMAKE_CXX_STANDARD_LIBRARIES : " ${CMAKE_CXX_STANDARD_LIBRARIES})
message("CMAKE_CXX_IMPLICIT_LINK_LIBRARIES : " ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
message("CMAKE_DEF_IMPLICIT_LINK_LIBRARIES : " ${CMAKE_DEF_IMPLICIT_LINK_LIBRARIES})