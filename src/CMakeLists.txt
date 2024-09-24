
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Add source to this project's executable.
#add_executable (cat 
#	"src/cat.cpp"      "include/cat.h" 
#	"src/cmd.cpp"      "include/cmd.hpp"
#	"src/caf.cpp"      "include/caf.hpp"
#	"src/log.cpp"      "include/log.hpp"

#	"src/data.cpp"     "include/data.hpp"
#	"src/pixel.cpp"    "include/pixel.hpp"
#	"src/cluster.cpp"  "include/cluster.hpp"
#	"src/sensor.cpp"   "include/sensor.hpp"
#	"src/coord.cpp"    "include/coord.hpp"
#	"src/plane.cpp"    "include/plane.hpp"
#	"src/layer.cpp"    "include/layer.hpp"
#	"src/hit.cpp"      "include/hit.hpp"
#)

# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - Main application target executable.
# ----------------------------------------------------------------------------------------------------------------------


# The main target executable.
add_executable (cat 
	
	# Core.
	"../src/acMain.cpp"
	"../src/acServer.cpp"
	"../src/acLoop.cpp"
	
	# Facilities.
	"../src/afFile.cpp"
	"../src/afFont.cpp"

	# Client.
	"../src/rcDCs.cpp"
	
	#GPs
	"../src/gpScene.cpp"
	


	#"../src/uiPad.cpp"
	#"../src/uiWindow.cpp"
	#"../src/uiSplash.cpp"
)

# Add its own sources to this project's executable.
target_include_directories(cat PRIVATE "../include/")

# The SDL library is used by the CAT application, but build independently.
# Look at the ''CMakeLists.txt' for building details.
target_include_directories(cat PRIVATE "../lib/SDL/include/SDL3/")


# The SDL_net library is built within the CAT application. Version
# used is 3.x.x, so be sure that the submodule repository branch
# is set to 'Main' (other branches are for older versions).
target_include_directories(cat PRIVATE "../lib/SDL_net/include/")
target_sources(cat PRIVATE 
	"../lib/SDL_net/src/SDL_net.c"
)

# The GLAD OpenGL loader facility is included into the main server build.
# Check and update it accordingly to the standard evolution.
target_include_directories(cat PRIVATE "../lib/glad/include/")
target_include_directories(cat PRIVATE "../lib/glad/include/glad/")


# The GLM lilbary (Open GL math) is used for all 3D calculations.
target_include_directories(cat PRIVATE "../lib/glm/")


# The FreetYpe library is used to handle fonts. It is used
# as pre-built binaries, so make sure to link accordingly
# the environment you compile within.
target_include_directories(cat PRIVATE "../lib/freetype/include/")

# The ''dirent.h' file for cross-platform POSIX file management.
target_include_directories(cat PRIVATE "../lib/dirent/")



# CAT server final executable sources.
#target_sources(cat PRIVATE 
	#"../src/acMain.cpp"		"../include/acMain.h"
#)

# Dear ImGUI is built within the CAT application.
target_include_directories(cat PRIVATE "../lib/imgui/")
target_sources(cat PRIVATE 
	"../lib/imgui/imgui.cpp"							"../lib/imgui/imgui.h"
														"../lib/imgui/imconfig.h"
														"../lib/imgui/imgui_internal.h"	
														"../lib/imgui/imstb_rectpack.h"
														"../lib/imgui/imstb_textedit.h"
														"../lib/imgui/imstb_truetype.h"
	"../lib/imgui/imgui_demo.cpp"
	"../lib/imgui/imgui_draw.cpp"
	"../lib/imgui/imgui_tables.cpp"
	"../lib/imgui/imgui_widgets.cpp"
	"../lib/imgui/backends/imgui_impl_sdl3.cpp"         "../lib/imgui/backends/imgui_impl_sdl3.h"
	"../lib/imgui/backends/imgui_impl_sdlrenderer3.cpp" "../lib/imgui/backends/imgui_impl_sdlrenderer3.h"
)



# ----------------------------------------------------------------------------------------------------------------------
# LINKING - Link the application to externally built libraries (see the '../lib/CMakeLists.txt' for details).
# ----------------------------------------------------------------------------------------------------------------------

# Add link to externally built libraries.

# Add link to externally built libraries.
message(STATUS "CAT: defining SDL own-built library dependencies...")
target_link_libraries(cat PRIVATE SDL)


# FreeType library
message(STATUS "CAT defining FreeType pre-compiled library dependencies...")
# TODO: pre-compiled library selection based on system
target_link_libraries(cat PRIVATE freetype)



# CMake version check.
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cat PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
