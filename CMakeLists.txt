cmake_minimum_required(VERSION 3.16)
project(2DRaytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(2DRaytracer
    main.cpp
)


# Link SFML libraries
target_link_libraries(2DRaytracer sfml-graphics sfml-window sfml-system)