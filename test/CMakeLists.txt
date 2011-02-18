###############################################################################
##
## CMakeLists file for unit test
##
###############################################################################

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCES
  t-hello
  t-synchronized_hello
  t-create_vector
  t-create_vector_cxx
  t-create_vector_in_scope
  #t-matrix-vector # deprecated
  #t-matrix-matrix # deprecated
  #t-matrix-matrix-matrix # deprecated
  )

FOREACH(current ${SOURCES})
  ADD_EXECUTABLE(${current} ${current}.cpp ${COMMON_SOURCES})
  ADD_TEST(${current} ${current})
  TARGET_LINK_LIBRARIES(${current} ${PROJECT_NAME} ${PETSC_LIBRARIES})
  INSTALL(TARGETS ${current} RUNTIME DESTINATION share/${PROJECT_NAME}/test COMPONENT test)
ENDFOREACH()

######################################################################################
