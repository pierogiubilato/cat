# ======================================================================================================================
# == CAT project - SERVER executable
# ======================================================================================================================

# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - CAT Server executable target.
# ----------------------------------------------------------------------------------------------------------------------

# The main server target executable.
# ------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "{CAT}--> -------------| Building Server |-------------")
message(STATUS "{CAT}--> [Server] setting up core...")

# Add the server executable.
add_executable (catServer)

# Set proper c++ standard..
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET catServer PROPERTY CXX_STANDARD 23)
endif()

# Add its own and common includes.
target_include_directories(catServer PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	cmake_path(GET ${CMAKE_CURRENT_SOURCE_DIR} PARENT_DIR) "/common/"
)

# Cat server own code.
target_sources(catServer PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/srvMain.cpp"
	
	#mingw32

	#"${CMAKE_CURRENT_SOURCE_DIR}/server/SampleBase.cpp"
	
	#"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentTools/Imgui/src/ImGuiUtils.cpp"
	#"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentTools/ThirdParty/Imgui/imgui.cpp"
	#"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentTools/ThirdParty/Imgui/imgui_draw.cpp"
	#"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentTools/ThirdParty/Imgui/imgui_tables.cpp"
	#"${PROJECT_SOURCE_DIR}/lib/Diligent/include/DiligentTools/ThirdParty/Imgui/imgui_widgets.cpp"


)

# OOF dependencies (quick consolle library, headers only)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Server] including OOF: ${PROJECT_SOURCE_DIR}/lib/oof")
target_include_directories(
	catServer PRIVATE 
	"${PROJECT_SOURCE_DIR}/lib/oof"
)

# SFML dependencies (statically linked library)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Server] target link SFML: " ${CAT_SDL3_LIB_DIR}/${CAT_SDL3_LIB})
target_link_libraries (
    catServer PRIVATE 
    sfml-graphics 
)

# ImGui dependencies (statically linked library)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Server] target link ImGui: " ${CAT_SDL3_LIB_DIR}/${CAT_SDL3_LIB})
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



