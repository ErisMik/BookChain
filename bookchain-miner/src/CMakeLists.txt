cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
project( bookchain_miner )


# Use clang-tidy as a sanity checker
# set( CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-fuchsia-default-arguments;" )


# JSON library dependency
set( JSON_BuildTests OFF CACHE INTERNAL "" )
set( JSON_Install OFF CACHE INTERNAL "" )
add_subdirectory( thirdparty/nlohmann_json )


# Main miner executable
add_executable( miner  miner.cpp block.cpp utils.cpp)
target_compile_options( miner PUBLIC "-Wall" )

target_include_directories( miner PUBLIC "${CMAKE_SOURCE_DIR}" SYSTEM PRIVATE "thirdparty/nlohmann_json/include/" )
target_link_libraries( miner PUBLIC pthread crypto PRIVATE nlohmann_json::nlohmann_json )
