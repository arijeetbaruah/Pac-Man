cmake_minimum_required(VERSION 3.16)
project(PacMan LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_Declare(GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(SFML GLM)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_subdirectory(plugins/spdlog)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE HEADERS_PP "include/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE RESOURCES "assets/*.rc")
file(GLOB_RECURSE RESOURCES_HEADER "assets/*.h")

add_executable(PacMan ${HEADERS} ${HEADERS_PP} ${SOURCES} ${RESOURCES} ${RESOURCES_HEADER})
target_link_libraries(PacMan PRIVATE sfml-graphics)
target_link_libraries(PacMan PRIVATE sfml-audio)
target_link_libraries(PacMan PRIVATE glm::glm)
target_link_libraries(PacMan PRIVATE spdlog::spdlog)
target_compile_features(PacMan PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET PacMan
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PacMan>
        VERBATIM)
endif()
