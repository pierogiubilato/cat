# ======================================================================================================================
# == CAT project - SERVER executable and CLIENT library cmake file
# ======================================================================================================================


# ----------------------------------------------------------------------------------------------------------------------
# SERVER - Overall settings.
# ----------------------------------------------------------------------------------------------------------------------

message(STATUS "{CAT}--> -------------| CAT |-------------")
message(STATUS "{CAT}--> Building on: " ${CMAKE_SYSTEM})
message(STATUS "{CAT}--> Building at: " ${PROJECT_SOURCE_DIR})



# ----------------------------------------------------------------------------------------------------------------------
# SYSTEM - Detect which system we are on.
# ----------------------------------------------------------------------------------------------------------------------

# Windows
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(CAT_SYS_WIN 1)

# Linux
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(CAT_SYS_LINUX 1)

# Mac OS
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CAT_SYS_MACOS 1)

# Not supported
else()
	set(CAT_SYS_UNSUPPORTED 1)

endif()


# ----------------------------------------------------------------------------------------------------------------------
# GRAPHICS APIs - Select which underlying graphics APIs the system has, and which to use.
# ----------------------------------------------------------------------------------------------------------------------

# Now check what is really available in the system.
message(STATUS "{CAT}--> ---------| Graphic API |---------")

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


# Diligent Engine - Pre-built binaries (build those you prefere in case, see how at 
# https://github.com/DiligentGraphics/DiligentEngine)

set(CAT_DILIGENT_INCLUDE "${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentCore/")
if(${BUILD_MODE} MATCHES "Debug")
	message(STATUS "{CAT}--> [Server] linking to DEBUG Diligent libraries")
	if(CAT_SERVER_GAPI MATCHES "D3D12")
		set(CAT_DILIGENT_LIB "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug/GraphicsEngineD3D12_64d.lib")
		set(CAT_DILIGENT_DLL "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug/GraphicsEngineD3D12_64d.dll")
	elseif(CAT_SERVER_GAPI MATCHES "OpenGL")
		set(CAT_DILIGENT_LIB "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug/GraphicsEngineOpenGL_64d.lib")
		set(CAT_DILIGENT_DLL "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug/GraphicsEngineOpenGL_64d.dll")
	elseif(CAT_SERVER_GAPI MATCHES "Vulkan")
		set(CAT_DILIGENT_LIB "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug/GraphicsEngineVk_64d.lib")
		set(CAT_DILIGENT_DLL "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-debug/GraphicsEngineVk_64d.dll")
	else()
		message(FATAL_ERROR "{CAT}--> ERROR: no suitable Diligent library available for DEBUG linking")
	endif()
elseif(${BUILD_MODE} MATCHES "Release")
	message(STATUS "{CAT}--> [Server] linking to RELEASE Diligent libraries")
	if(CAT_SERVER_GAPI MATCHES "D3D12")
		set(CAT_DILIGENT_LIB "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release/GraphicsEngineD3D12_64.lib")
		set(CAT_DILIGENT_DLL "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release/GraphicsEngineD3D12_64.dll")
	elseif(CAT_SERVER_GAPI MATCHES "OpenGL")
		set(CAT_DILIGENT_LIB "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release/GraphicsEngineOpenGL_64.lib")
		set(CAT_DILIGENT_DLL "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release/GraphicsEngineOpenGL_64.dll")
	elseif(CAT_SERVER_GAPI MATCHES "Vulkan")
		set(CAT_DILIGENT_LIB "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release/GraphicsEngineVk_64.lib")
		set(CAT_DILIGENT_DLL "${PROJECT_SOURCE_DIR}/lib/Diligent/x64-release/GraphicsEngineVk_64.dll")
	else()
		message(FATAL_ERROR "{CAT}--> ERROR: no suitable Diligent library available for RELEASE linking")
	endif()
else()
	message(FATAL_ERROR "{CAT}--> ERROR: no suitable Diligent DLLs available for the current building mode")
endif()


# SDL3 - Pre-built binaries (build those you prefere in case, see how at 
# https://github.com/libsdl-org/SDL
set(CAT_SDL3_INCLUDE "${PROJECT_SOURCE_DIR}/lib/SDL/include/")
if(${BUILD_MODE} MATCHES "Debug")
	message(STATUS "{CAT}--> [Server] linking to DEBUG SDL3 library")
	set(CAT_SDL3_LIB "${PROJECT_SOURCE_DIR}/lib/SDL/x64-debug/lib/SDL3.lib")
	set(CAT_SDL3_DLL "${PROJECT_SOURCE_DIR}/lib/SDL/x64-debug/bin/SDL3.dll")
elseif(${BUILD_MODE} MATCHES "Release")
	message(STATUS "{CAT}--> [Server] linking to RELEASE SDL3 library")
		set(CAT_SDL3_LIB "${PROJECT_SOURCE_DIR}/lib/SDL/x64-release/SDL3.lib")
		set(CAT_SDL3_DLL "${PROJECT_SOURCE_DIR}/lib/SDL/x64-release/SDL3.dll")
else()
	message(FATAL_ERROR "{CAT}--> ERROR: no suitable SDL3 DLLs available for the current building mode")
endif()



# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - Application server executable target.
# ----------------------------------------------------------------------------------------------------------------------

# The main server target executable.
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> -----------| Server |-----------")
message(STATUS "{CAT}--> [Server] setting up core...")
add_executable (catServer)

# Set proper c++ standard..
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET catServer PROPERTY CXX_STANDARD 23)
endif()

# Add its own and common includes.
target_include_directories(catServer PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/common/"
	"${CMAKE_CURRENT_SOURCE_DIR}/server/"
)

# Cat server own code.
target_sources(catServer PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/server/main.cpp"
)



# SDL dependencies.
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Server] including SDL3...")
target_include_directories(catServer PRIVATE CAT_SDL3_INCLUDE)
target_link_libraries(catServer PRIVATE CAT_SDL3_LIB)



# SDL_net dependencies.
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Server] including SDL_net (built within)...")

# The SDL_net library is built within the CAT application. Version
# used is 3.x.x, so be sure that the submodule repository branch
# is set to 'Main' (other branches are for older versions).
target_include_directories(catServer PRIVATE 
	"${PROJECT_SOURCE_DIR}/lib/SDL_net/include"
)

# SDL_net is built within the target, so add its own files..
target_sources(catServer PRIVATE 
	"${PROJECT_SOURCE_DIR}/lib/SDL_net/src/SDL_net.c"
)

# Diligent Core dependencies.
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Server] including Diligent Core...")
message(STATUS "{CAT}--> [Server] ${CAT_DILIGENT_INCLUDE}")

target_compile_options(catServer PRIVATE -DUNICODE)
target_include_directories(catServer PRIVATE CAT_DILIGENT_INCLUDE)
target_link_libraries(catServer PRIVATE CAT_DILIGENT_LIB)




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
# BUILDING - Application client library target.
# ----------------------------------------------------------------------------------------------------------------------

