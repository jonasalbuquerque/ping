set(BINARY ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TESTS LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TESTS})

add_executable(${BINARY} ${TESTS})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)