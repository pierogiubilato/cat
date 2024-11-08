# ======================================================================================================================
# == CAT project - CLIENT library
# ======================================================================================================================


# ----------------------------------------------------------------------------------------------------------------------
# CMAKE - Overall settings.
# ----------------------------------------------------------------------------------------------------------------------

# Cmake minimum.
cmake_minimum_required(VERSION 3.28)



# ----------------------------------------------------------------------------------------------------------------------
# BUILDING - CAT Client library target.
# ----------------------------------------------------------------------------------------------------------------------

# The main server target executable.
# ------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "{CAT}--> -----------------| Client |-------------------")
message(STATUS "{CAT}--> setting up core...")

# Add the server executable.
add_library (catClient STATIC)

# Set proper c++ standard..
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET catClient PROPERTY CXX_STANDARD 23)
endif()

# Add its own and common includes.
target_include_directories(catClient PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../common"
)

# Cat client own code.
target_sources(catClient PRIVATE 
	"client.cpp"
	"../common/cmd.cpp"
	"../common/console.cpp"
)


# OOF dependencies (quick consolle library, headers only)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> including OOF: ${PROJECT_SOURCE_DIR}/lib/oof")
target_include_directories(
	catClient PRIVATE 
	"${PROJECT_SOURCE_DIR}/lib/oof"
)


# SFML dependencies (statically linked library, network only)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> target link SFML network: ${SFML}")
target_link_libraries (
    catClient PRIVATE 
    sfml-network 
)






# ----------------------------------------------------------------------------------------------------------------------
# PREPARING - CAT Client headers.
# ----------------------------------------------------------------------------------------------------------------------

# Move the relevant headers to the include folder
# ------------------------------------------------------------------------------

#message(STATUS "{CAT}--> [CLient] library written to ${CMAKE_CURRENT_BINARY_DIR}")
#
#add_custom_command (
#	TARGET catClient POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy 
#    
#	# Headers.
#	"${CMAKE_CURRENT_SOURCE_DIR}/client.hpp"
#	"${CMAKE_CURRENT_SOURCE_DIR}/../common/console.hpp"
#	"${CMAKE_CURRENT_SOURCE_DIR}/../common/cmd.hpp"
#	
#	# Library.
#	"${CMAKE_CURRENT_BINARY_DIR}/catClient.lib"
#	
#	# Target dir.
#	"${CAT_INCLUDE_DIR}/cat/"
#)
