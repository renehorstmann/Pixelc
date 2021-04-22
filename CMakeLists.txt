cmake_minimum_required(VERSION 3.0)
project(Pixelc C)

# Optional definitions set:
# OPTION_GLES           for OpenGLES3.0 instead of OpenGL3.3
# OPTION_GLEW           if GLEW is available
# OPTION_SDL            is set to let rhc code use SDL function
# -not used- OPTION_TTF            to use ro_ttftext
# -not used- OPTION_GYRO           if gyro sensor is available
# -not used- OPTION_GL_ERROR       if set, functions use r_render_check_error (heavy op, if summed up)
# OPTION_TOUCH          to compile with touchscreen usage
#
# NDEBUG                is used at some points, too
# MATHC_NO_PRINT_COLOR  disable colored mathc prints
# NUKLEAR_SCALE=3.0     for small hd screens (smartphones)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wno-long-long -Wno-unused-function -Wno-unused-variable -Wno-missing-braces")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
        "${PROJECT_SOURCE_DIR}/include/*"
        "${PROJECT_SOURCE_DIR}/src/*"
        "${PROJECT_SOURCE_DIR}/src/e/*"
        "${PROJECT_SOURCE_DIR}/src/r/*"
        "${PROJECT_SOURCE_DIR}/src/u/*"
        "${PROJECT_SOURCE_DIR}/src/p/*"
        )

add_executable(pixelc ${SRCS})

# Desktop or Mobile? -> GL or GLES?
find_library(GL_LIB GL)
find_library(GLES_LIB GLESv3)
if (GL_LIB)
    message("GL found: Desktop mode")
    target_link_libraries(pixelc ${GL_LIB})
elseif (GLES_LIB)
    message("GLES found: Mobile mode")
    add_definitions(-DOPTION_GLES)
    add_definitions(-DOPTION_SDL)
    add_definitions(-DOPTION_TOUCH)
    add_definitions(-DMATHC_NO_PRINT_COLOR)
    add_definitions(-DNUKLEAR_SCALE=3.0)
    target_link_libraries(pixelc ${GLES_LIB})
else ()
    message(FATAL_ERROR "Neither GL nor GLESv3 found, exiting CMake")
endif ()

# GLEW
find_library(GLEW_LIB GLEW)
if(GLEW_LIB)
    add_definitions(-DOPTION_GLEW)
    target_link_libraries(pixelc ${GLEW_LIB})
endif()

# SDL
# -not used- add_definitions(-DOPTION_TTF)
find_package(SDL2 REQUIRED)
if (GL_LIB)
    find_library(SDL2_IMAGE_LIBRARIES SDL2_image)
    #find_library(SDL2_TTF_LIBRARIES SDL2_ttf)
else ()
    find_package(SDL2_image REQUIRED)
    #find_package(SDL2_ttf REQUIRED)
endif ()
include_directories(${SDL2_INCLUDE_DIRS})
message("include dir:" ${SDL2_INCLUDE_DIRS})
target_link_libraries(pixelc m
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        #${SDL2_TTF_LIBRARIES}
        )

# res
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
