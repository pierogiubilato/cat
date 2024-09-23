

# ******************************************************************************
# ** External libraries repositories
# ******************************************************************************




# ------------------------------------------------------------------------------
# -- SDL 3
# ------------------------------------------------------------------------------

# The SDL library is built here from the SDL submodules, using the following 
# switches to define which modules, and with which options, are actually 
# included into the final DLL.
# In the main "CMakeLists.txt" file CMake must be instructed to copy the built
# DLL into the app executable dir. Otherwise, the library build path must be
# added to the general path.
message(STATUS "CAT: Configuring SDL build environment...")

# SDL setup.
set(SDL_TEST OFF)				# Avoid building the tests.
set(SDL_AUDIO_DEFAULT OFF)		# Avoid the audio subsystem.
set(SDL_JOYSTICK_DEFAULT OFF)	# Avoid the joystick subsystem.
set(SDL_HAPTIC_DEFAULT OFF)		# Necessary when joystick set to off.
set(SDL_SENSOR_DEFAULT OFF)		# Avoid sensors subsystem.
set(SDL_CAMERA_DEFAULT OFF)		# Avoid camera subsystem.
set(SDL_HIDAPI_DEFAULT OFF)		# Avoid HID device direct handling.
set(SDL_POWER_DEFAULT OFF)		# Avoid power management subsystem.

# General SDL library object.
add_subdirectory(SDL)
add_library(SDL INTERFACE)
target_link_libraries(SDL INTERFACE SDL3::SDL3)


# ------------------------------------------------------------------------------
# -- Dear GuIMG
# ------------------------------------------------------------------------------

# The Dear GuIMG library implements the user interface system. It is bult
# within the application from a submodule repository of the code.


# ------------------------------------------------------------------------------
# -- FreeType
# ------------------------------------------------------------------------------

# The FreeType library is stored in the freetype submodule, and uses the
# pre-built binaries for the specific system, due to the complexity of building
# them outside GNU systems.
# In the main "CMakeLists.txt" file CMake must be instructed to copy the correct
# DLL binary into the app executable dir accordingly to the target system.
message(STATUS "CAT: Configuring FreeType pre-built library...")
add_library(freetype SHARED IMPORTED)

configure_file(
	"${CMAKE_SOURCE_DIR}/lib/freetype/release dll/win64/freetype.lib"
	"${CMAKE_CURRENT_BINARY_DIR}/freetype.lib"
	COPYONLY
)
configure_file(
	"${CMAKE_SOURCE_DIR}/lib/freetype/release dll/win64/freetype.dll"
	"${CMAKE_CURRENT_BINARY_DIR}/freetype.dll"
	COPYONLY
)

# TODO set correct compiled library depending on system. 
#set_target_properties(freetype PROPERTIES 
#	IMPORTED_LOCATION_DEBUG "${CMAKE_SOURCE_DIR}/lib/freetype/realease dll/win64/freetype.lib"
#	IMPORTED_LOCATION_RELEASE "${CMAKE_SOURCE_DIR}/lib/freetype/realease dll/win64/freetype.lib"
#	IMPORTED_LOCATION_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/lib/freetype/realease dll/win64/freetype.lib"
#	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/lib/freetype/include/freetype/"
#)


# ------------------------------------------------------------------------------
# -- Open GL through GLAD multi platform library
# ------------------------------------------------------------------------------

# GLAD provides a loader and bindings for the OpenGL library. It is built
# within the application itself, from a direct download from the GLAD website.
# In alternative, the GLEW library could be used, using the same bindings.



# ------------------------------------------------------------------------------
# -- GLM 
# ------------------------------------------------------------------------------

# GLM provides several math tools for OpenGL and general 3D geometry 
# calculations. Being an h-only library, it is incorporated as submodules 
# and simply included in the application.




