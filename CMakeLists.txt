cmake_minimum_required(VERSION 3.8)
project(sparse LANGUAGES C)
MESSAGE(STATUS "PROJECT_NAME: " ${PROJECT_NAME})

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Check compiler architecture
if(CMAKE_CL_64)
    MESSAGE( STATUS "64-bit")
else()
    MESSAGE( STATUS "32-bit")
endif()

# Check compilers
MESSAGE( STATUS ">>>>>>>> ${CMAKE_C_COMPILER_ID}")
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    MESSAGE( STATUS "Using Clang" )
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    MESSAGE( STATUS "Using GNU" )
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    MESSAGE( STATUS "Using MSVC" )
endif()

set(
    SOURCES
    inc/spConfig.h
    inc/spDefs.h
    inc/spMatrix.h
    src/spAllocate.c
    src/spBuild.c
    src/spFactor.c
    src/spFortran.c
    src/spOutput.c
    src/spSolve.c
    src/spTest.c
    src/spUtils.c
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(sparse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(sparse PUBLIC ${PROJECT_INCLUDE_DIRS})

# Set installation directory
install(TARGETS ${PROJECT_NAME}
        EXPORT ${TARGETS_EXPORT_NAME}
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib)

#if(WINDOWS)
#    install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/win/bin/" DESTINATION ${PROJECT_SOURCE_DIR}/dist)
#elseif(LINUX)
#    if (CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
#        install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/linux/" DESTINATION ${PROJECT_SOURCE_DIR}/dist)
#    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l OR ARM32_BUILD)
#        install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/arm32/" DESTINATION ${PROJECT_SOURCE_DIR}/dist)
#    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL aarch64)
#        install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/aarch64/" DESTINATION ${PROJECT_SOURCE_DIR}/dist)
#    endif()
#elseif(MACOS)
#    install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/macos/" DESTINATION ${PROJECT_SOURCE_DIR}/dist)
#endif()

#add_executable(${PROJECT_NAME} main.c)
#target_link_libraries(${PROJECT_NAME} )
