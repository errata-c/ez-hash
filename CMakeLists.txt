cmake_minimum_required(VERSION 3.16)

project(EZ_HASH
VERSION 0.2.1
LANGUAGES C CXX)

include(GNUInstallDirs)
include("cmake/ez-cmake/install_package.cmake")

option(BUILD_TESTS "Build the test executables" ON)
option(SEPARATE_DIRECTORY "Install the package into its own directory" ON)
set(CONFIG_DIR "${CMAKE_INSTALL_DATAROOTDIR}/ez-hash" CACHE STRING "The relative directory to install package config files.")


find_package(xxHash CONFIG REQUIRED)

file(COPY 
	"submodules/pcg-cpp/include/pcg_random.hpp" 
	"submodules/pcg-cpp/include/pcg_extras.hpp"
	"submodules/pcg-cpp/include/pcg_uint128.hpp"
	
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/include/ez/hash/pcg"
)

add_library(hash STATIC
	"src/murmur.cpp"
	"src/xorshift.cpp"
	"src/splitmix.cpp"
	"src/xxhash.cpp"
)
target_include_directories(hash PUBLIC 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(hash PUBLIC xxHash::xxhash)
target_compile_features(hash PUBLIC cxx_std_17)

add_library("ez::hash" ALIAS "hash")

# Build the tests once the option is enabled.
if(BUILD_TESTS)
	add_subdirectory("tests")
endif()

if(SEPARATE_DIRECTORY) 
	set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/ez-hash)
endif()

install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	TYPE INCLUDE
	FILES_MATCHING
	PATTERN "*.h" PATTERN "*.hpp"
)
install(TARGETS hash
	EXPORT "ez-hash-export"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)

install_package(
	NAME "ez-hash"
	EXPORT "ez-hash-export"
	VERSION "${CMAKE_PROJECT_VERSION}"

	NAMESPACE "ez::"

	COMPATIBILITY "SameMajorVersion"
	DESTINATION "${CONFIG_DIR}"

	PRECONFIG "cmake/preconfig.cmake"
)