######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(petsc-cxx)

SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

######################################################################################


######################################################################################
### 2) Include useful features
######################################################################################

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

FIND_PACKAGE(PETSc REQUIRED)

INCLUDE_DIRECTORIES(
  ${PETSC_INCLUDES}
)

######################################################################################


######################################################################################
### 3) Include header files path
######################################################################################

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

######################################################################################


######################################################################################
### 4) Set compiler definitions
######################################################################################

IF(UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
  # ADD_DEFINITIONS( -g3 )
ENDIF()

######################################################################################


######################################################################################
### 5) Prepare some variables for CMAKE usage
######################################################################################

SET(SAMPLE_SRCS)

######################################################################################


######################################################################################
### 6) Now where we go ?
######################################################################################

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(application)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(doc)

######################################################################################


######################################################################################
### 7) Create executable, link libraries and prepare target
######################################################################################

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SAMPLE_SRCS})
INSTALL(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib COMPONENT libraries)

######################################################################################
