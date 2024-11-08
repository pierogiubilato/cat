# ======================================================================================================================
# == CAT project - SERVER executable and CLIENT library cmake file
# ======================================================================================================================


# ----------------------------------------------------------------------------------------------------------------------
# CMAKE - Overall settings.
# ----------------------------------------------------------------------------------------------------------------------

# Cmake minimum.
cmake_minimum_required(VERSION 3.28)

# Retrieve contents from GitHub.
include(FetchContent)



# ----------------------------------------------------------------------------------------------------------------------
# APPLICATION - Overall settings.
# ----------------------------------------------------------------------------------------------------------------------

message(STATUS "")
message(STATUS "{CAT}--> -------------------| CAT |-------------------")
message(STATUS "{CAT}--> Building on: " ${CMAKE_SYSTEM})
message(STATUS "{CAT}--> Building at: " ${PROJECT_SOURCE_DIR})



# ----------------------------------------------------------------------------------------------------------------------
# SYSTEM - Detect which system we are on.
# ----------------------------------------------------------------------------------------------------------------------

# Windows
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(CAT_SYS_WIN 1)
	message(STATUS "{CAT}--> System is: Windows")

# Linux
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(CAT_SYS_LINUX 1)
	message(STATUS "{CAT}--> System is: Linux")

# Mac OS
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CAT_SYS_MACOS 1)
	message(STATUS "{CAT}--> System is: Mac OS")

# Not supported
else()
	set(CAT_SYS_UNSUPPORTED 1)
	message(FATAL_ERROR "{CAT}--> System is: UNSOPPORTED")

endif()


# ----------------------------------------------------------------------------------------------------------------------
# WINDOWS and GUI common libraries - Retrieves the libraries from GitHub repositories
# ----------------------------------------------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "{CAT}--> -------------| System Libraries |------------")

# SFML and ImGui are built WITHIN the application.
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


# SFML and ImGui versions.
set(SFML_VERSION 2.5.1)
set(IMGUI_VERSION 1.87)

# Retrieve latest SFML to build it within the application.
message(STATUS "{CAT}--> fetching SFML from https://github.com/SFML/SFML.git") 
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# SFML building options.
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" ON)


# ----------------------------------------------------------------------------------------------------------------------
# TARGETS - each target makefile is defined within the target folder
# ----------------------------------------------------------------------------------------------------------------------

# Client static library.
add_subdirectory(client)

# Server application.
add_subdirectory(server)

# Files in common between the server and the client.
add_subdirectory(common)




#if(WIN32)
#    add_custom_command(
#        TARGET main
#        COMMENT "Copy OpenAL DLL"
#        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
#        VERBATIM)
#endif()



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



