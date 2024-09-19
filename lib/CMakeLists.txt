# Libraries repositories (likely git submodules)


# ------------------------------------------------------------------------------
# -- SDL 3
# ------------------------------------------------------------------------------


# The SDL library is built from the SDL submodules, using the following switches
# define which part modules, and with which options, are actually included into 
# the final DLL.
# In the main "CMakeLists.txt" file CMake must be instructed to copy the bilu
# DLL into the app executable dir. Otherwise, the library build path must be
# added to the general path.

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
# -- Open GL through GLFW multi platform library
# ------------------------------------------------------------------------------

# General SDL library object.
#add_subdirectory(glfw)
#add_library(glfw INTERFACE)
#target_link_libraries(glfw INTERFACE glfw::glfw)
