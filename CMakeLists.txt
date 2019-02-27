cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.1.3)

project(testdot LANGUAGES CXX
       VERSION 0.1.0.1)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(AUTHOR "Edoardo Pasca")
set(AUTHOR_DETAILS "edo.paskino@gmail.com")
set(DESCRIPTION "Yet another Particle Swarm Algorithm in C++")
option(BUILD_DOCS "Build with API Docs" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(ENABLE_OPENMP "Allow user to activate/deactivate OpenMP support" ON)


if (ENABLE_OPENMP)
  #include(FindOpenMP)
  find_package(OpenMP)
  if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_STATIC_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_STATIC_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()
  if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP for C++ Compiler Found, version ${OpenMP_Fortran_VERSION_MAJOR}.${OpenMP_Fortran_VERSION_MINOR}")
  else()
    message(ERROR_CRITICAL "No OpenMP support detected")
  endif()
endif()

message(STATUS "building ${PROJECT_NAME}, version ${PROJECT_VERSION}")
message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
include(GNUInstallDirs)
include(FeatureSummary)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(PSO2)

if(BUILD_DOCS)
  find_package(Doxygen REQUIRED)
  configure_file(${PROJECT_SOURCE_DIR}/cmake/Doxyfile.cmake ${PROJECT_BIN_DIR}Doxyfile)
  add_custom_target(docs
    ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile)
endif()

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
