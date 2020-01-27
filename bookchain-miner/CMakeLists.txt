cmake_minimum_required( VERSION 3.10 )
set( CMAKE_CXX_STANDARD 17 )
project( bookchain_miner )


# Find clang-tidy executable
find_program( CLANG_TIDY_EXE NAMES "clang-tidy" )
if( NOT CLANG_TIDY_EXE )
  message( STATUS "clang-tidy not found." )
else()
  message( STATUS "clang-tidy found: ${CLANG_TIDY_EXE}" )
  set( DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-fuchsia-default-arguments,-fuchsia-default-arguments-calls,-modernize-use-trailing-return-type" )
endif()


# JSON library dependency
set( JSON_BuildTests OFF CACHE INTERNAL "" )
set( JSON_Install OFF CACHE INTERNAL "" )
add_subdirectory( thirdparty/nlohmann_json )


# Libbookchain
set( LIBBOOKCHAIN_SOURCES src/block.cpp src/utils.cpp src/crypto.cpp src/chain.cpp src/storage.cpp )
add_library( libbookchain SHARED ${LIBBOOKCHAIN_SOURCES} )
target_compile_options( libbookchain PUBLIC "-Wall" )
target_include_directories( libbookchain PUBLIC "src/" SYSTEM PRIVATE "thirdparty/nlohmann_json/include/" )
target_link_libraries( libbookchain PUBLIC pthread crypto PRIVATE nlohmann_json::nlohmann_json )


# Main miner executable
set( MINER_SOURCES src/miner.cpp )
add_executable( miner ${MINER_SOURCES} )
target_compile_options( miner PUBLIC "-Wall" )
target_include_directories( miner PUBLIC "src/" )
target_link_libraries( miner PUBLIC libbookchain )


# Build tests
if ( ENABLE_MINER_TESTS )
    enable_testing()
    set( TEST_BOOKCHAIN_SOURCES test/test.cpp test/test_block.cpp )
    add_executable( test_bookchain ${TEST_BOOKCHAIN_SOURCES} )
    target_include_directories( test_bookchain SYSTEM PRIVATE "thirdparty/catch/" "src/" )
    target_link_libraries( test_bookchain PUBLIC libbookchain )

    add_test( libbookchain test_bookchain )
endif()


# Use clang-tidy as a sanity checker for miner and test
if ( ENABLE_CLANG_TIDY_CHECK AND CLANG_TIDY_EXE )
    set_target_properties( libbookchain PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
    set_target_properties( miner PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
    set_target_properties( test_bookchain PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
endif()
