# ======================================================================================================================
# == CAT project - COMMON components
# ======================================================================================================================



# Server application and client library common translation units.
# ------------------------------------------------------------------------------
message(STATUS "")
message(STATUS "{CAT}--> -----------------| Common |------------------")
message(STATUS "{CAT}--> setting up include dirs...")


# Add Server common includes.
target_include_directories(catServer PRIVATE 
	"${PROJECT_SOURCE_DIR}/include/cat"
)

# Add Client common includes.
target_include_directories(catClient PRIVATE 
	"${PROJECT_SOURCE_DIR}/include/cat"
)