# ======================================================================================================================
# == CAT project - CLIENT library and example
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
message(STATUS "{CAT}--> -------------| Building Client |-------------")
message(STATUS "{CAT}--> [CLient] setting up core...")

# Add the server executable.
add_executable (catClient)

# Set proper c++ standard..
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET catClient PROPERTY CXX_STANDARD 23)
endif()

# Add its own and common includes.
target_include_directories(catClient PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}"
	cmake_path(GET ${CMAKE_CURRENT_SOURCE_DIR} PARENT_DIR) "/common"
)

# Cat client own code.
target_sources(catClient PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/catClient.cpp"
)

# OOF dependencies (quick consolle library, headers only)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Client] including OOF: ${PROJECT_SOURCE_DIR}/lib/oof")
target_include_directories(
	catClient PRIVATE 
	"${PROJECT_SOURCE_DIR}/lib/oof"
)


# SFML dependencies (statically linked library, network only)
# ------------------------------------------------------------------------------
message(STATUS "{CAT}--> [Client] target link SFML network: ${SFML}")
target_link_libraries (
    catClient PRIVATE 
    sfml-network 
)


