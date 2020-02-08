cmake_minimum_required(VERSION 3.10)
project(testTest)
find_package(LLVM 9.0 REQUIRED CONFIG
              PATHS ${search_paths}
              NO_DEFAULT_PATH)
set (search_paths
        ${PATH_TO_LLVM}
        ${PATH_TO_LLVM}/lib/cmake
        ${PATH_TO_LLVM}/lib/cmake/llvm
        ${PATH_TO_LLVM}/lib/cmake/clang
        ${PATH_TO_LLVM}/share/clang/cmake/
        ${PATH_TO_LLVM}/share/llvm/cmake/
        )
set(CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_FLAGS "-g -o3 -lpthread -lgflags")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(CMAKE_CXX_STANDARD 14)
# waisted me a huge amount of time when there are some undefined functions found during makefile, always try brute force clang++ command first and find required components
#using llvm-config --components
llvm_map_components_to_libnames(llvm_libs support core irreader executionengine target orcjit mcjit interpreter native nativecodegen asmparser selectiondag)
#If you omit the include_directories(src), your tests will not be able to find the header files.
include_directories(src)
include_directories(src/AST)
add_subdirectory(src)
#add_subdirectory(src/AST)
add_subdirectory(tests)
add_subdirectory(cache)
add_subdirectory(lib/googletest)
#add_executable(testTest main.cpp)