# ======================================================================================================================
# == CAT project - Master project cmake file
# ======================================================================================================================



# CMAKE settings.
# ---------------



# Minimum CMake version.
cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project properties.
# -------------------

# Project Name. This call sets the ${PROJECT_SOURCE_DIR} the one of this file.
project (
	"cat"
    VERSION 0.1
	DESCRIPTION "C++ Acquisition and Analysis Toolset"
	HOMEPAGE_URL "https://github.com/pierogiubilato/cat"
	LANGUAGES CXX
)

# C standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build mode
SET(BUILD_MODE Debug)


# As we link dinamically, makes the lib dll already in the source output directory.
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


# Set project folders.
# ------------------------------------------------------------------------------------------
set(CAT_EXAMPLES_DIR "${PROJECT_SOURCE_DIR}/examples")
set(CAT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(CAT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set(CAT_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/resources")
set(CAT_SRC_DIR "${PROJECT_SOURCE_DIR}/src")


# The actual proprietary project code. Look at the "../src/CMakeLists.txt" file for details.
# ------------------------------------------------------------------------------------------
add_subdirectory(src)


# Th examples which uses the client library
# -----------------------------------------------------------------------------------------------
add_subdirectory(examples)