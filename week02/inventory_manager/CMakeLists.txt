cmake_minimum_required(VERSION 3.20)

project(InventoryManager)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

set(CMAKE_GENERATOR "Ninja")

# Header files
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/database
    ${PROJECT_SOURCE_DIR}/include/interfaces
    ${PROJECT_SOURCE_DIR}/include/managers
    ${PROJECT_SOURCE_DIR}/include/models
)

# Source files
file(GLOB_RECURSE SOURCES
    src/database/*.cpp
    src/interfaces/*.cpp
    src/managers/*.cpp
    src/models/*.cpp
    src/main.cpp
    )

add_executable(inventory_manager ${SOURCES})

# Link SQLite3
target_link_libraries(inventory_manager ${SQLite3_LIBRARIES})