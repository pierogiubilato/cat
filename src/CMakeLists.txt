
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


# CAT build - Main application target executable.
# ----------------------------------------------------------------------------------------------------------------------

# The main target executable.
add_executable (cat 

	"../src/acMain.cpp"		"../include/acMain.h"
	"../src/acLoop.cpp"		"../include/acLoop.h"
	"../src/acServer.cpp"	"../include/acServer.h"

)

# Add its own sources to this project's executable.
target_include_directories(cat PRIVATE "../include/")
target_sources(cat PRIVATE 
	#"../src/acMain.cpp"		"../include/acMain.h"
)

# Set path with respect to the source folder.



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

# CAT link - Link the application to externally built libraries (see the '../lib/CMakeLists.txt' for details).
# ----------------------------------------------------------------------------------------------------------------------

# Add link to externally built libraries.
target_link_libraries(cat PRIVATE SDL)


# CMake version check.
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cat PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
