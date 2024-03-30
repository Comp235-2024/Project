cmake_minimum_required(VERSION 3.26)
project(Project)

add_compile_options(-Wcpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG 9ccA280)

FetchContent_MakeAvailable(SFML json)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

# Include directories for each component
include_directories(components/Characters/include)
include_directories(components/ItemContainers/include)
include_directories(components/Items/include)
include_directories(components/Log/include)
include_directories(components/Maps/include)
include_directories(components/GameEngine/include)
include_directories(components/Functionalities/include)

# Add the source files for each subdirectory
file(GLOB_RECURSE SOURCES
        "components/Characters/src/*.cpp"
        "components/ItemContainers/src/*.cpp"
        "components/Items/src/*.cpp"
        "components/Log/src/*.cpp"
        "components/Maps/src/*.cpp"
        "components/GameEngine/src/*.cpp"
        "components/Functionalities/src/*.cpp")


# Define the executable
add_executable(Project ${SOURCES}
        components/GameEngine/include/CharacterCreator.h
        components/GameEngine/src/CharacterCreator.cpp)

# Link the executable with the SFML and JSON libraries
target_link_libraries(Project PRIVATE sfml-graphics nlohmann_json::nlohmann_json)

if(WIN32)
    add_custom_command(
            TARGET Project POST_BUILD
            COMMENT "Copy OpenAL DLL"
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
            $<TARGET_FILE_DIR:Project>
            VERBATIM)
endif()

install(TARGETS Project)