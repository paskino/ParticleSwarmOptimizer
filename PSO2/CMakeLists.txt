add_library(libpso SHARED Bird.cpp Swarm.cpp)
set_property(TARGET libpso PROPERTY CXX_STANDARD 11)
message(STATUS "C++ Standard ${CXX_STANDARD}")
if (${BUILD_SHARED_LIBS})
  set_target_properties(libpso PROPERTIES 
    VERSION ${testdot_VERSION}
    SOVERSION ${testdot_VERSION_MAJOR})
endif()
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
target_include_directories(libpso PUBLIC "${PROJECT_SOURCE_DIR}/PSO2/include")
add_executable(testpso 
  PSO2.cpp
  )
target_link_libraries(testpso libpso)
install(TARGETS libpso testpso
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(FILES $<TARGET_PROPERTY:libpso,INCLUDE_DIRECTORIES>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
