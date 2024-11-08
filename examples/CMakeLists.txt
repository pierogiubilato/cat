# ======================================================================================================================
# == CAT project - EXAMPLES executables
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
message(STATUS "{CAT}--> ----------------| Examples |-----------------")
message(STATUS "{CAT}--> setting up core...")

# Add the examples executable(s).
add_executable (exmp_01)

# Set proper c++ standard..
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET exmp_01 PROPERTY CXX_STANDARD 23)
endif()

# Add its own and common includes.
target_include_directories(
	exmp_01 PRIVATE 
#	"${CMAKE_CURRENT_SOURCE_DIR}"
#	"../include"
)

# Examples own code.
target_sources(exmp_01 PRIVATE 
	"exmp_01.cpp"
)



# CAT client dependencies.
# ------------------------------------------------------------------------------

# Add include files.
message(STATUS "{CAT}--> including CAT client: ${PROJECT_SOURCE_DIR}/include/cat")
target_include_directories(
	exmp_01 PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"../include/cat"
	"../include/oof"
)


# Link to the library
message(STATUS "{CAT}--> linking to CAT client library: ${CMAKE_CURRENT_SOURCE_DIR}/../include/cat/")
target_link_libraries(
	exmp_01 PRIVATE
	catClient
	#"${CMAKE_CURRENT_SOURCE_DIR}/../include/cat/client.lib"
)
