cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
project( bookchain_miner )


# JSON library dependency
set( JSON_BuildTests OFF CACHE INTERNAL "" )
set( JSON_Install OFF CACHE INTERNAL "" )
add_subdirectory( thirdparty/nlohmann_json )


# Main miner executable
add_executable( miner  miner.cpp )
target_compile_options( miner PUBLIC "-Wall" )

target_include_directories( miner SYSTEM PRIVATE "thirdparty/nlohmann_json/include/" )
target_link_libraries( miner PUBLIC pthread PRIVATE nlohmann_json::nlohmann_json )
