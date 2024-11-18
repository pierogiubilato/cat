# ======================================================================================================================
# == CAT project - SERVER executable
# ======================================================================================================================

# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - CAT Server executable target.
# ----------------------------------------------------------------------------------------------------------------------

# The main server target executable.
# ------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "{CAT}--> -----------------| Server |------------------")
message(STATUS "{CAT}--> setting up core...")

# Add the server executable.
add_executable (catServer)

# Set proper c++ standard.
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET catServer PROPERTY CXX_STANDARD 20)
endif()

# Add its own and common includes.
target_include_directories(catServer PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"../common"
	"../common/co"
	"../common/gp"
	"../common/ui"
)

# Cat server own code.
target_sources(catServer PRIVATE 
	
	# Server only components.
	"server.cpp"
	"window.cpp"
	"gui.cpp"
		
	# Server-Client shared components.
	"../common/coAbc.cpp"
	"../common/co/coSet.cpp"
	"../common/co/coDrawable.cpp"
	"../common/co/coStreamable.cpp"
	
	"../common/ui/uiAbc.cpp"
	"../common/ui/uiButton.cpp"

	# End-User Server and Client shared components.
	"../common/cmd.cpp"
	"../common/console.cpp"
)


# ----------------------------------------------------------------------------------------------------------------------
# GRAPHICS APIs - Select which underlying graphics APIs the system has, and which to use.
# ----------------------------------------------------------------------------------------------------------------------

# Check for Vulkan
find_package(Vulkan)
if (VULKAN_FOUND)
    message(STATUS "{CAT}--> Found Vulkan")
#    #target_include_directories(catServer PRIVATE ${Vulkan_INCLUDE_DIRS})
#    #target_link_libraries (catServer PRIVATE Vulkan::Vulkan)
	set(CAT_AVAILABLE_VULKAN)
endif ()

# Check for OpenGL
find_package(OpenGL)
if (OPENGL_FOUND)
    message(STATUS "{CAT}--> Found OpenGL")
	#target_include_directories(catServer PRIVATE ${OpenGL_INCLUDE_DIRS})
	#target_link_libraries (catServer PRIVATE OpenGL::OpenGL)
	set(CAT_AVAILABLE_OPENGL)
endif ()

# Check for DirectX12
if(CAT_SYS_WIN)
    message(STATUS "{CAT}--> On Windows, DirectX 12 available")
	#set(CAT_AVAILABLE_D3D12)
endif ()


# Choose which library to use.
if (CAT_SYS_WIN)
	
	# On Windows, use DirectX 12 by default.
	set(CAT_SERVER_GAPI "D3D12")

elseif(CAT_SYS_LINUX)

	# On Linux, prefer Vulkan if available, otherwise use "good old" OpenGL.
	if(VULKAN_FOUND)
		set(CAT_SERVER_GAPI "Vulkan")
	elseif(OPENGL_FOUND)
		set(CAT_SERVER_GAPI "OpenGL")
	else()
		message(FATAL_ERROR "{CAT}--> ERROR: no suitable Graphics API available on Linux")
	endif()

elseif(CAT_SYS_MACOS)
	
	# On MAC, OpenGL is deprecated, so try Vulkan (through MeltedVK)
	if(VULKAN_FOUND)
		set(CAT_SERVER_GAPI "Vulkan")
	else()
		message(FATAL_ERROR "{CAT}--> ERROR: no suitable Graphics API available on Mac OS")
	endif()
endif()

# Show chosen one.
message(STATUS "{CAT}--> [Server] selected graphic API: ${CAT_SERVER_GAPI}")



# ----------------------------------------------------------------------------------------------------------------------
# GRAPHICS Libraries - Set the paths for the pre-built libraries.
# ----------------------------------------------------------------------------------------------------------------------


# Diligent Engine - Pre-built binaries (build those you prefere in case, see 
# how at https://github.com/DiligentGraphics/DiligentEngine)
# ------------------------------------------------------------------------------
set(CAT_DILIGENT_INCLUDE 
	"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentCore"
	"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentSamples"
	"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentTools"
)
if(${BUILD_MODE} MATCHES "Debug")
	
	# Set debug libraries folder. 
	message(STATUS "{CAT}--> linking to DEBUG Diligent libraries")
	set(CAT_DILIGENT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug")
	
	# Set specific graphic library based on selected API.
	if(CAT_SERVER_GAPI MATCHES "D3D12")
		set(CAT_DILIGENT_LIB "GraphicsEngineD3D12_64d.lib")
		set(CAT_DILIGENT_DLL "GraphicsEngineD3D12_64d.dll")
	elseif(CAT_SERVER_GAPI MATCHES "OpenGL")
		set(CAT_DILIGENT_LIB "GraphicsEngineOpenGL_64d.lib")
		set(CAT_DILIGENT_DLL "GraphicsEngineOpenGL_64d.dll")
	elseif(CAT_SERVER_GAPI MATCHES "Vulkan")
		set(CAT_DILIGENT_LIB "GraphicsEngineVk_64d.lib")
		set(CAT_DILIGENT_DLL "GraphicsEngineVk_64d.dll")
	else()
		message(FATAL_ERROR "{CAT}--> ERROR: no suitable Diligent library available for DEBUG linking")
	endif()
elseif(${BUILD_MODE} MATCHES "Release")
	
	# Set debug libraries folder.
	message(STATUS "{CAT}--> linking to RELEASE Diligent libraries")
	set(CAT_DILIGENT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release")
	
	# Set specific graphic library based on selected API.
	if(CAT_SERVER_GAPI MATCHES "D3D12")
		set(CAT_DILIGENT_LIB "GraphicsEngineD3D12_64.lib")
		set(CAT_DILIGENT_DLL "GraphicsEngineD3D12_64.dll")
	elseif(CAT_SERVER_GAPI MATCHES "OpenGL")
		set(CAT_DILIGENT_LIB "GraphicsEngineOpenGL_64.lib")
		set(CAT_DILIGENT_DLL "GraphicsEngineOpenGL_64.dll")
	elseif(CAT_SERVER_GAPI MATCHES "Vulkan")
		set(CAT_DILIGENT_LIB "GraphicsEngineVk_64.lib")
		set(CAT_DILIGENT_DLL "GraphicsEngineVk_64.dll")
	else()
		message(FATAL_ERROR "{CAT}--> ERROR: no suitable Diligent library available for RELEASE linking")
	endif()
else()
	message(FATAL_ERROR "{CAT}--> ERROR: no suitable Diligent DLLs available for the current building mode")
endif()



# ----------------------------------------------------------------------------------------------------------------------
# WINDOWS and GUI Libraries - Retrieves the libraries from GitHub repositories
# ----------------------------------------------------------------------------------------------------------------------

# Retrieve latest ImGui to build it within the application.
message(STATUS "{CAT}--> fetching ImGui from https://github.com/ocornut/imgui.git")
FetchContent_Declare(
	ImGui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG        v1.89.9
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)


# Retrieve latest SFML-ImGui to build it within the application.
message(STATUS "{CAT}--> fetching ImGui-SFML from https://github.com/SFML/imgui-sfml")
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)


# OOF dependencies (quick consolle library, headers only)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> including OOF: ${PROJECT_SOURCE_DIR}/lib/oof")
target_include_directories(
	catServer PRIVATE 
	"${PROJECT_SOURCE_DIR}/include/oof"
)

# SFML dependencies (statically linked library)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> target link SFML: ${SFML}")
target_link_libraries (
    catServer PRIVATE 
    sfml-graphics
	sfml-network
)

# ImGui dependencies (statically linked library)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> target link ImGui-SFML: ${ImGui_SFML}" )
target_link_libraries (
    catServer PRIVATE 
    ImGui-SFML::ImGui-SFML
)

# SDL dependencies.
# ------------------------------------------------------------------------------
#message(STATUS "{CAT}--> [Server] including SDL3: " ${CAT_SDL3_INCLUDE})
#target_include_directories(
#	catServer PRIVATE 
#	${CAT_SDL3_INCLUDE}
#)
#message(STATUS "{CAT}--> [Server] target link SDL3: " ${CAT_SDL3_LIB_DIR}/${CAT_SDL3_LIB})
#target_link_libraries(
#	catServer PRIVATE 
#	"${CAT_SDL3_LIB_DIR}/${CAT_SDL3_LIB}"
#)
#target_link_libraries(catServer PRIVATE SDL3:SDL3-shared)


# SDL_net dependencies.
# ------------------------------------------------------------------------------
#message(STATUS "{CAT}--> [Server] including SDL_net (built within)...")

# The SDL_net library is built within the CAT application. Version
# used is 3.x.x, so be sure that the submodule repository branch
# is set to 'Main' (other branches are for older versions).
#target_include_directories(catServer PRIVATE 
#	"${PROJECT_SOURCE_DIR}/lib/SDL_net/include"
#)

# SDL_net is built within the CAT application, so add it to the target.
#target_sources(catServer PRIVATE 
#	"${PROJECT_SOURCE_DIR}/lib/SDL_net/src/SDL_net.c"
#)






# Diligent Core dependencies.
# ------------------------------------------------------------------------------
#message(STATUS "{CAT}--> [Server] including Diligent Core...")
#target_compile_options(catServer PRIVATE -DUNICODE)
#target_include_directories(catServer PRIVATE ${CAT_DILIGENT_INCLUDE})
#target_link_libraries(catServer PRIVATE "${CAT_DILIGENT_LIB_DIR}/${CAT_DILIGENT_LIB}")




# imGUI dependencies.
# ------------------------------------------------------------------------------
#message(STATUS "{CAT}--> [Server] including imGUI (built within)...")

#target_include_directories(catServer PRIVATE 
#	"../lib/imgui/"
#)

# Dear ImGUI is built within the CAT application, so add it to the target.
#target_sources(catServer PRIVATE 
#	"../lib/imgui/imgui.cpp"							"../lib/imgui/imgui.h"
#														"../lib/imgui/imconfig.h"
#														"../lib/imgui/imgui_internal.h"	
#														"../lib/imgui/imstb_rectpack.h"
#														"../lib/imgui/imstb_textedit.h"
#														"../lib/imgui/imstb_truetype.h"
#	"../lib/imgui/imgui_demo.cpp"
#	"../lib/imgui/imgui_draw.cpp"
#	"../lib/imgui/imgui_tables.cpp"
#	"../lib/imgui/imgui_widgets.cpp"
#	"../lib/imgui/backends/imgui_impl_sdl3.cpp"         "../lib/imgui/backends/imgui_impl_sdl3.h"
#	"../lib/imgui/backends/imgui_impl_sdlrenderer3.cpp" "../lib/imgui/backends/imgui_impl_sdlrenderer3.h"
#)





# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - Post build commands
# ----------------------------------------------------------------------------------------------------------------------

# Copy Diligent DLLs in the binary output folder.
#add_custom_command(
#        TARGET catServer POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CAT_DILIGENT_LIB_DIR}/${CAT_DILIGENT_DLL}
#                ${CMAKE_CURRENT_BINARY_DIR}/${CAT_DILIGENT_DLL}
#)

# Copy SDL3 DLLs in the binary output folder.
#add_custom_command(
#        TARGET catServer POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CAT_SDL3_LIB_DIR}/${CAT_SDL3_DLL}
#                ${CMAKE_CURRENT_BINARY_DIR}/${CAT_SDL3_DLL}
#)



