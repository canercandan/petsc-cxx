FILE(GLOB HDRS *.h ${PROJECT_NAME})
INSTALL(FILES ${HDRS} DESTINATION include/${PROJECT_NAME} COMPONENT headers)

FILE(GLOB SOURCES *.cpp)
SET(SAMPLE_SRCS ${SOURCES} PARENT_SCOPE)
