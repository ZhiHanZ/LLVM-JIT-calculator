set(BINARY ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
find_package(glog REQUIRED CONFIG NAMES google-glog glog)
if (NOT TARGET glog::glog)
    find_library(LIB_glog NAMES glog)
else()
    set(LIB_glog glog::glog)
endif (NOT TARGET glog::glog)
set(SOURCES ${TEST_SOURCES})
add_subdirectory(AST)

add_executable(${BINARY} ${TEST_SOURCES})
#
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest glog::glog  ${llvm_libs})