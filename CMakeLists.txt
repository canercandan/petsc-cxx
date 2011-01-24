# http://code.google.com/p/eigentools/source/browse/trunk/CMake/?r=2
# https://github.com/jedbrown/cmake-modules/blob/master/FindPETSc.cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(petsc-wrapper)

IF (UNIX)
  SET( CMAKE_C_FLAGS "-fPIC -Wall -Wansi -Werror -Wwrite-strings -Wno-strict-aliasing ${CMAKE_CXX_FLAGS}")
ENDIF()

INCLUDE(${CMAKE_SOURCE_DIR}/CMake/FindPETSc.cmake)
#INCLUDE(${CMAKE_SOURCE_DIR}/CMake/FindSLEPc.cmake) # doesnot work yet!
FIND_PACKAGE(Boost 1.33.0)

INCLUDE_DIRECTORIES(
  ${PETSC_INCLUDES}
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

SET(COMMON_SOURCES
  Printable.cpp
  Persistent.cpp
  )

SET(SOURCES
  t-hello
  t-synchronized_hello
  t-create_vector
  t-create_vector_cxx
  t-create_vector_in_scope
  )

FOREACH(current ${SOURCES})
  ADD_EXECUTABLE(${current} ${current}.cpp ${COMMON_SOURCES})
  ADD_TEST(${current} ${current})
  TARGET_LINK_LIBRARIES(${current} ${PETSC_LIBRARIES} ${Boost_LIBRARIES})
ENDFOREACH()
