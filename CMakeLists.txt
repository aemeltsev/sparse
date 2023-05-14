cmake_minimum_required(VERSION 3.10)
project(sparse
    VERSION 1.4
    HOMEPAGE_URL https://github.com/aemeltsev/sparse
    DESCRIPTION "A Sparse Linear Equation Solver"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(DEFAULT_BUILD_TYPE "Release")

set(SPARSE_BUILD)
option(SPARSE_SHARED "Shared build" OFF)
option(SPARSE_STATIC "Static build" ON)
option(SPARSE_USE_C99 "" OFF)
option(SPARSE_USE_TEST "Enable Tests" OFF)

if(CMAKE_SYSTEM_NAME STREQUAL WASI)
  set(SPARSE_STATIC ON CACHE BOOL "Static option" FORCE)
  set(SPARSE_SHARED OFF CACHE BOOL "Shared option" FORCE)
endif()

if(NOT SPARSE_STATIC AND SPARSE_SHARED)
  set(SPARSE_BUILD SHARED)
else(SPARSE_STATIC)
  set(SPARSE_BUILD STATIC)
endif()

if(SPARSE_USE_C99)
  set(CMAKE_C_STANDARD 99)
endif()

if(MSVC)
  add_definitions(-DNDEBUG -D_WINDOWS -D_USRDLL)
  add_compile_options(/W3 /Ox /Gy /Oi /TC)
  
  # Ref: https://skia.googlesource.com/third_party/sdl/+/refs/heads/master/CMakeLists.txt#225
  # Make sure /RTC1 is disabled, otherwise it will use functions from the CRT
  foreach(flag_var
      CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
    string(REGEX REPLACE "/RTC(su|[1su])" "" ${flag_var} "${${flag_var}}")
  endforeach(flag_var)
else()
    add_compile_options(-Wall -O3 )#-Werror)
endif()

get_directory_property(SparseParentDir PARENT_DIRECTORY)

if(NOT SparseParentDir AND NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

if(NOT CPack_CMake_INCLUDED)
  include(CPack)
endif()

# Target Start
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

add_library(${PROJECT_NAME}
    ${SPARSE_BUILD}
    ${SOURCES})

if(SPARSE_SHARED)
    add_definitions(-DSPARSE_EXPORTS)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DSPARSE_STATIC)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
                           VERSION ${PROJECT_VERSION}
                           SOVERSION ${PROJECT_VERSION_MAJOR})

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION_MAJOR})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

## Target for header-only usage
add_library(${PROJECT_NAME}_headers INTERFACE)
target_include_directories(${PROJECT_NAME}_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})

# Test Configuration
if(SPARSE_USE_TEST)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

# Set installation directory
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY lib DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PATTERN ".*" EXCLUDE)

# Config
#export(TARGETS ${PROJECT_NAME}
#    NAMESPACE ${PROJECT_NAME}::
#    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
#    )

#install(EXPORT ${PROJECT_NAME}
#    FILE "${PROJECT_NAME}Config.cmake"
#    NAMESPACE ${PROJECT_NAME}::
#    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

#set(PACKAGE_NAME ${PROJECT_NAME})
#set(prefix ${CMAKE_INSTALL_PREFIX})
#set(exec_prefix ${CMAKE_INSTALL_PREFIX})
#if (IS_ABSOLUTE "${CMAKE_INSTALL_INCLUDEDIR}")
#    set(includedir "${CMAKE_INSTALL_INCLUDEDIR}")
#else()
#    set(includedir "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
#endif()
#if (IS_ABSOLUTE "${CMAKE_INSTALL_LIBDIR}")
#    set(libdir "${CMAKE_INSTALL_LIBDIR}")
#else()
#    set(libdir "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
#endif()
#set(PACKAGE_VERSION "${PROJECT_VERSION}")
#configure_file(sparse.pc.in sparse.pc @ONLY)

#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sparse.pc
#    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
