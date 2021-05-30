cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME BackwardSlicing)

# setup names
set(LLVM_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/llvm-project-10.0.1)
message(STATUS "llvm-root == ${LLVM_ROOT_DIR}" )
set(LLVM_BUILD_DIR ${LLVM_ROOT_DIR}/build)
# set(LLVM_BUILD_ROOT ${LLVM_ROOT_DIR})

# clang 10
# set(CMAKE_CXX_COMPILER "${LLVM_BUILD_DIR}/bin/clang++")
# set(CMAKE_C_COMPILER "${LLVM_BUILD_DIR}/bin/clang")

find_package(LLVM REQUIRED
    HINTS "${PROJECT_SOURCE_DIR}/llvm-project-10.0.1/build"
    )
    #NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
#find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_INCLUDE_DIRS})

message(STATUS "LLVM ${LLVM_PACKAGE_VERSION} found.")
message(STATUS "CLANG ${CLANG_CXX_COMPILER} ${CC}")

add_library(${PROJECT_NAME} MODULE
    script/pass.cpp
)

# add_subdirectory(script)

# Add this line to avoid error:
#     undefined symbol: _ZN4llvm23EnableABIBreakingChecksE'
if (NOT LLVM_ENABLE_RTTI)
    # set(CMAKE_CXX_FLAGS "-fno-rtti")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fno-rtti")
endif()


