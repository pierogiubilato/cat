# CMakeList.txt : CMake project for cat, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Language
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project properties.
# -------------------

# Project Name
project ("cat")

# As we link dinamically, makes the lib dll already in the source output directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# The actual proprietary project code. Look at the "../src/CMakeLists.txt" file for details.
# ------------------------------------------------------------------------------------------
add_subdirectory(src)



# All the libraries the project depends on. Look at the "../lib/CMakeLists.txt" file for details.
# -----------------------------------------------------------------------------------------------
add_subdirectory(lib)