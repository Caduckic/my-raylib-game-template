if(NOT "${PLATFORM}" STREQUAL "Web")
    if(WIN32)
        set (CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
    else()
        set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
    endif()
endif()