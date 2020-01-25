cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
project( bookchain_miner )


# Find clang-tidy executable
find_program( CLANG_TIDY_EXE NAMES "clang-tidy" )
if( NOT CLANG_TIDY_EXE )
  message( STATUS "clang-tidy not found." )
else()
  message( STATUS "clang-tidy found: ${CLANG_TIDY_EXE}" )
  set( DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-fuchsia-default-arguments" )
endif()


# JSON library dependency
set( JSON_BuildTests OFF CACHE INTERNAL "" )
set( JSON_Install OFF CACHE INTERNAL "" )
add_subdirectory( thirdparty/nlohmann_json )


# Main miner executable
add_executable( miner  src/miner.cpp src/block.cpp src/utils.cpp src/crypto.cpp src/chain.cpp src/storage.cpp)
target_compile_options( miner PUBLIC "-Wall" )

target_include_directories( miner PUBLIC "${CMAKE_SOURCE_DIR}/src" SYSTEM PRIVATE "thirdparty/nlohmann_json/include/" )
target_link_libraries( miner PUBLIC pthread crypto PRIVATE nlohmann_json::nlohmann_json )


# Use clang-tidy as a sanity checker for miner
if ( CLANG_TIDY_EXE )
    set_target_properties( miner PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
endif()
