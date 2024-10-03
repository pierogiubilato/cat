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
	DESCRIPTION "CMake example for Direct3D 11 Game (Win32)"
	LANGUAGES CXX
)

# C standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build mode
SET(BUILD_MODE Debug)


# Set the necessary libraries paths.
# ------------------------------------------------------------------------------------------





# As we link dinamically, makes the lib dll already in the source output directory.
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


# The actual proprietary project code. Look at the "../src/CMakeLists.txt" file for details.
# ------------------------------------------------------------------------------------------
add_subdirectory(src)


# All the libraries the project depends on. Look at the "../lib/CMakeLists.txt" file for details.
# -----------------------------------------------------------------------------------------------
#add_subdirectory(lib)

