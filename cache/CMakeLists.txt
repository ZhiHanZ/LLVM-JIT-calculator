set(BINARY ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
find_package(glog REQUIRED CONFIG NAMES google-glog glog)