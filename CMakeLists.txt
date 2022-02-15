cmake_minimum_required(VERSION 3.0)
project(pixelc C)

# Optional definitions set:
# OPTION_GLES           for OpenGLES3.0 instead of OpenGL3.3
# OPTION_GLEW           if GLEW is available
# OPTION_SDL            is set to let rhc code use SDL function
# OPTION_FETCH          to use u_fetch (http rest)
# OPTION_SOCKET         to use rhc sockets
# OPTION_TTF            to use ro_ttftext
# OPTION_GYRO           if gyro sensor is available
# OPTION_SANITIZER      use sanitizer checks for debugging
# -not used- OPTION_GL_ERROR       if set, functions use r_render_check_error (heavy op, if summed up)
#
# NDEBUG                is used at a few points, too
# MATHC_NO_PRINT_COLOR  disable colored mathc prints
# NUKLEAR_SCALE=3.0     for small hd screens (smartphones)
# RHC_LOG_DO_NOT_PRINT_TIME_FILE disable time and file in logs

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long -Wno-unused-function -Wno-unused-variable -Wno-missing-braces -Wno-unused-parameter")


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


# set default configuration
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to Debug as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message("Using build type: " ${CMAKE_BUILD_TYPE})

# check platform
if (MINGW)
    message("Platform: Windows MinGW")
    set(PLATFORM_MINGW true)
else ()
    find_library(GL_LIB GL)
    find_library(GLES_LIB GLESv3)
    if (GL_LIB)
        message("Platform: Unix")
        set(PLATFORM_UNIX true)
    elseif (GLES_LIB)
        message("Platform: Mobile")
        set(PLATFORM_MOBILE true)
    else ()
        message(FATAL_ERROR "Platform: unknown, neither GL nor GLES found!")
    endif ()
endif ()

# all platforms:
# add_definitions(-DOPTION_FETCH)
# add_definitions(-DOPTION_SOCKET)
# add_definitions(-DOPTION_TTF)
target_link_libraries(pixelc m)

# windows
if (PLATFORM_MINGW)
    message("Setup Windows MinGW")
    # mingw is not shipped with a find_package(SDL2) script
    add_definitions(-Dmain=SDL_main)
    add_definitions(-DOPTION_GLEW)
    add_definitions(-DOPTION_SDL)
    add_definitions(-DMATHC_NO_PRINT_COLOR)

    # mingw may not find pixelc library, due to missing CMAKE_LIBRARY_PATH lib paths
    find_library(OPENGL_LIB opengl32 REQUIRED)
    find_library(GLEW_LIB glew32 REQUIRED)
    find_library(GLU_LIB glu32 REQUIRED)

    target_link_libraries(pixelc m
            mingw32
            SDL2main
            SDL2
            SDL2_image
            SDL2_net
            SDL2_ttf
            curl
            ${OPENGL_LIB}
            ${GLEW_LIB}
            ${GLU_LIB}
            )
endif ()


# unix
if (PLATFORM_UNIX)
    message("Setup Unix")

    # using sanitizer
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("Using Google sanitizer")
        add_definitions(-DOPTION_SANITIZER)
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
        set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
    endif ()

    find_package(SDL2 REQUIRED)
    find_library(SDL2_IMAGE_LIBRARIES SDL2_image REQUIRED)
    find_library(SDL2_NET_LIBRARIES SDL2_net REQUIRED)
    find_library(SDL2_TTF_LIBRARIES SDL2_ttf REQUIRED)

    find_library(CURL_LIBRARIES curl REQUIRED)

    find_library(GL_LIB GL REQUIRED)

    target_link_libraries(pixelc
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_NET_LIBRARIES}
            ${SDL2_TTF_LIBRARIES}
            ${CURL_LIBRARIES}
            ${GL_LIB}
            )

    # not necessary in unix
    find_library(GLEW_LIB GLEW)
    if (GLEW_LIB)
        add_definitions(-DOPTION_GLEW)
        target_link_libraries(pixelc ${GLEW_LIB})
    endif ()
endif ()


# mobile
if (PLATFORM_MOBILE)
    message("Setup Mobile")
    add_definitions(-DOPTION_GLES)
    add_definitions(-DOPTION_SDL)
    add_definitions(-DMATHC_NO_PRINT_COLOR)
    add_definitions(-DNUKLEAR_SCALE=3.0)
    add_definitions(-DRHC_LOG_DO_NOT_PRINT_TIME_FILE)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_net REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    find_package(CURL REQUIRED)

    find_library(GLES_LIB GLESv3 REQUIRED)

    target_link_libraries(pixelc
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_NET_LIBRARIES}
            ${SDL2_TTF_LIBRARIES}
            ${CURL_LIBRARIES}
            ${GLES_LIB}
            )
endif ()

# res
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
