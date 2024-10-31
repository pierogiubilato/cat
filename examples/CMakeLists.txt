# ======================================================================================================================
# == CAT project - Examples cmake file
# ======================================================================================================================

# ----------------------------------------------------------------------------------------------------------------------
# CMAKE - Overall settings.
# ----------------------------------------------------------------------------------------------------------------------

# Cmake minimum.
cmake_minimum_required(VERSION 3.28)



# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - CAT Server executable target.
# ----------------------------------------------------------------------------------------------------------------------


# The main server target executable.
# ------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "{CAT}--> ------------| Setting Examples |-------------")
message(STATUS "{CAT}--> [Examples] setting up core...")

# Add the server executable.
add_executable (basic)

# Set proper c++ standard..
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET basic PROPERTY CXX_STANDARD 23)
endif()

# Add its own and common includes.
target_include_directories(basic PRIVATE 
#	"${CMAKE_CURRENT_SOURCE_DIR}"
#	"../include"
)

# Examples own code.
target_sources(basic PRIVATE 
	"basic.cpp"
)

# CAT client dependencies.
# ------------------------------------------------------------------------------

# Add include files.
message(STATUS "{CAT}--> [Examples] including CAT client: ${PROJECT_SOURCE_DIR}/include/cat")
target_include_directories(
	basic PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"../include/cat"
)



# Link to the library
message(STATUS "{CAT}--> [Examples] linking to CAT client library: ${CMAKE_CURRENT_SOURCE_DIR}/../include/cat/")
target_link_libraries(
	basic 
	catClient
	#"${CMAKE_CURRENT_SOURCE_DIR}/../include/cat/client.lib"
)
