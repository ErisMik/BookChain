cmake_minimum_required( VERSION 3.11 )
set( CMAKE_CXX_STANDARD 17 )
project( bookchain_miner )

include( FetchContent )

# Find clang-tidy executable
find_program( CLANG_TIDY_EXE NAMES "clang-tidy" )
if( NOT CLANG_TIDY_EXE )
  message( STATUS "clang-tidy not found." )
else()
  message( STATUS "clang-tidy found: ${CLANG_TIDY_EXE}" )
  set( DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-fuchsia-default-arguments,-fuchsia-default-arguments-calls,-modernize-use-trailing-return-type" )
endif()


# Find include-what-you-use executable
find_program( IWYU_EXE NAMES "include-what-you-use" "iwyu" )
if( NOT IWYU_EXE )
  message( STATUS "include-what-you-use not found." )
else()
  message( STATUS "include-what-you-use found: ${IWYU_EXE}" )
endif()


# NLohmann JSON dependency
set( JSON_BuildTests OFF CACHE INTERNAL "" )
set( JSON_Install OFF CACHE INTERNAL "" )
add_subdirectory( thirdparty/nlohmann_json )


# Oat++ Dependency
find_package( oatpp 1.0.0 )
if( NOT ${oatpp_FOUND} )
  message( WARNING "Oatpp dependency not found, will be fetched and built as a part of this build" )

  FetchContent_Declare( oatppcmake
    GIT_REPOSITORY https://github.com/oatpp/oatpp.git
    GIT_TAG 27c46444dbac6af79172b1600c7fcc99ff6df42b
  )

  FetchContent_GetProperties( oatppcmake )
  if( NOT oatppcmake_POPULATED )
    FetchContent_Populate( oatppcmake )
    add_subdirectory( ${oatppcmake_SOURCE_DIR} ${oatppcmake_BINARY_DIR} )
    add_library( oatpp::oatpp ALIAS oatpp )
  endif()
endif()


# Libbookchain
set( LIBBOOKCHAIN_SOURCES src/block.cpp src/utils.cpp src/crypto.cpp src/chain.cpp src/chaintools.cpp src/storage.cpp src/peers.cpp src/difficulty.cpp src/http/server.cpp )
add_library( bookchain STATIC ${LIBBOOKCHAIN_SOURCES} )
target_compile_options( bookchain PUBLIC "-Wall" "-Wextra" "-Wpedantic" )
target_include_directories( bookchain PUBLIC "src/" SYSTEM PRIVATE "thirdparty/nlohmann_json/include/" )
target_link_libraries( bookchain PUBLIC pthread crypto oatpp::oatpp nlohmann_json::nlohmann_json )


# Main exectuable
set( MINER_SOURCES src/main.cpp )
add_executable( miner ${MINER_SOURCES} )
target_compile_options( miner PUBLIC "-Wall" "-Wextra" "-Wpedantic" )
target_include_directories( miner PUBLIC "src/" )
target_link_libraries( miner PUBLIC bookchain )


# Build tests
if ( ENABLE_MINER_TESTS )
    enable_testing()
    set( TEST_BOOKCHAIN_SOURCES test/test.cpp test/test_block.cpp test/test_chaintools.cpp test/test_smoketests.cpp )
    add_executable( test_bookchain ${TEST_BOOKCHAIN_SOURCES} )
    target_include_directories( test_bookchain SYSTEM PRIVATE "thirdparty/catch/" "src/" )
    target_link_libraries( test_bookchain PUBLIC bookchain )

    add_test( libbookchain test_bookchain )
endif()


# Use clang-tidy as a sanity checker for miner and test
if ( ENABLE_CLANG_TIDY_CHECK AND CLANG_TIDY_EXE )
    set_target_properties( bookchain PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
    set_target_properties( miner PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
    set_target_properties( test_bookchain PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" )
endif()


# Use IWYU as a sanity checker for miner
if ( ENABLE_IWYU_CHECK AND IWYU_EXE )
    set_target_properties( bookchain PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXE}" )
    set_target_properties( miner PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXE}" )
endif()
