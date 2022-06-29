cmake_minimum_required(VERSION 3.0)
project(pixelc C)

# link options
set(USE_SDL_MIXER false)
set(USE_SDL_NET false)
set(USE_SDL_TTF false)
set(USE_FETCH false)
set(USE_SANITIZER true)

# Platforms definitions:
# PLATFORM_MSVC         Microsoft C++ Compiler
# PLATFORM_MINGW        Windows Msys2 Mingw-w64
# PLATFORM_UNIX         Ubuntu, etc.
# PLATFORM_MOBILE       Android
# PLATFORM_EMSCRIPTEN   emscripten web compiler

# Optional definitions:
# OPTION_GLES           for OpenGLES3.0 instead of OpenGL3.3
# OPTION_GLEW           if GLEW is available
# OPTION_SDL            is set to let s code use SDL function
# OPTION_FETCH          to use u_fetch (http rest)
# OPTION_SOCKET         to use s sockets (SDL_net needed if OPTION_SDL)
# OPTION_TTF            to use ro_ttftext (SDL_ttf needed)
# OPTION_GYRO           if gyro sensor is available
# OPTION_SANITIZER      use sanitizer checks for debugging
# -not used- OPTION_GL_ERROR       if set, functions use r_render_check_error (heavy op, if summed up)
#
# NDEBUG                is used at a few points, too
# M_NO_PRINT_COLOR  disable colored m prints
# S_LOG_DO_NOT_USE_COLOR          dont use colored logs
# S_LOG_DO_NOT_PRINT_TIME_FILE    disable time and file in logs

set(CMAKE_C_STANDARD 11)

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
        "${PROJECT_SOURCE_DIR}/src/dialog/*"
        "${PROJECT_SOURCE_DIR}/src/tool/*"
        )

add_executable(pixelc ${SRCS})


# set default configuration
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to Debug as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()
message("Using build type: " ${CMAKE_BUILD_TYPE})

# check platform
if (MINGW)
    message("Platform: Windows MinGW")
    add_definitions(-DPLATFORM_MINGW)
    set(PLATFORM_MINGW true)
elseif (WIN32)
    message("Plarform: Windows MSVC")
    add_definitions(-DPLATFORM_MSVC)
    set(PLATFORM_MSVC true)
else ()
    find_library(GL_LIB GL)
    find_library(GLES_LIB GLESv3)
    if (GL_LIB)
        message("Platform: Unix")
        add_definitions(-DPLATFORM_UNIX)
        set(PLATFORM_UNIX true)
    elseif (GLES_LIB)
        message("Platform: Mobile")
        add_definitions(-DPLATFORM_MOBILE)
        set(PLATFORM_MOBILE true)
    else ()
        message(FATAL_ERROR "Platform: unknown, neither GL nor GLES found!")
    endif ()
endif ()


# all platforms:
if (USE_SDL_MIXER)
    message("USE_SDL_MIXER")
endif ()
if (USE_SDL_NET)
    message("USE_SDL_NET")
    add_definitions(-DOPTION_SOCKET)
endif ()
if (USE_SDL_TTF)
    message("USE_SDL_TTF")
    add_definitions(-DOPTION_TTF)
endif ()
if (USE_FETCH)
    message("USE_FETCH")
    add_definitions(-DOPTION_FETCH)
endif ()

# windows mingw
if (PLATFORM_MINGW)
    message("Setup Windows MinGW")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long -Wno-unused-function -Wno-unused-variable -Wno-missing-braces -Wno-unused-parameter -Wno-format-truncation")

    # mingw is not shipped with a find_package(SDL2) script
    add_definitions(-Dmain=SDL_main)
    add_definitions(-DOPTION_GLEW)

    # mingw may not find a few libraries, due to missing CMAKE_LIBRARY_PATH lib paths
    find_library(OPENGL_LIB opengl32 REQUIRED)
    find_library(GLEW_LIB glew32 REQUIRED)
    find_library(GLU_LIB glu32 REQUIRED)

    target_link_libraries(pixelc
            m
            mingw32
            SDL2main
            SDL2
            SDL2_image
            ${OPENGL_LIB}
            ${GLEW_LIB}
            ${GLU_LIB}
            )

    if (USE_SDL_MIXER)
        target_link_libraries(pixelc SDL2_mixer)
    endif ()
    if (USE_SDL_NET)
        target_link_libraries(pixelc SDL2_net)
    endif ()
    if (USE_SDL_TTF)
        target_link_libraries(pixelc SDL2_ttf)
    endif ()
    if (USE_FETCH)
        target_link_libraries(pixelc curl)
    endif ()
endif ()

# windows msvc
if (PLATFORM_MSVC)
    message("Setup Windows MSVC")

    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4267 /wd4244 /wd4305 /wd4996 /wd5105")

    add_definitions(-Dmain=SDL_main)
    add_definitions(-DOPTION_GLEW)

    find_package(SDL2 REQUIRED)
    find_package(SDL2-image CONFIG REQUIRED)
    find_package(GLEW REQUIRED)

    target_link_libraries(pixelc
            SDL2::SDL2
            SDL2::SDL2main
            SDL2::SDL2_image
            GLEW::GLEW
            )

    if (USE_SDL_MIXER)
        find_package(SDL2-mixer CONFIG REQUIRED)
        target_link_libraries(pixelc SDL2::SDL2_mixer)
    endif ()
    if (USE_SDL_NET)
        find_package(SDL2-net CONFIG REQUIRED)
        target_link_libraries(pixelc SDL2::SDL2_net)
    endif ()
    if (USE_SDL_TTF)
        find_package(SDL2-ttf CONFIG REQUIRED)
        target_link_libraries(pixelc SDL2::SDL2_ttf)
    endif ()
    if (USE_FETCH)
        find_package(CURL CONFIG REQUIRED)
        target_link_libraries(pixelc CURL::libcurl)
    endif ()
endif ()


# unix
if (PLATFORM_UNIX)
    message("Setup Unix")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long -Wno-unused-function -Wno-unused-variable -Wno-missing-braces -Wno-unused-parameter -Wno-format-truncation")

    if (USE_SANITIZER)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            message("Using Google sanitizer")
            add_definitions(-DOPTION_SANITIZER)
            set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
            set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
        endif ()
    endif ()

    find_package(SDL2 REQUIRED)
    find_library(SDL2_IMAGE_LIBRARIES SDL2_image REQUIRED)

    find_library(GL_LIB GL REQUIRED)

    target_link_libraries(pixelc
            m
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${GL_LIB}
            )

    # not necessary in unix
    find_library(GLEW_LIB GLEW)
    if (GLEW_LIB)
        add_definitions(-DOPTION_GLEW)
        target_link_libraries(pixelc ${GLEW_LIB})
    endif ()

    if (USE_SDL_MIXER)
        find_library(SDL2_MIXER_LIBRARIES SDL2_mixer REQUIRED)
        target_link_libraries(pixelc ${SDL2_MIXER_LIBRARIES})
    endif ()
    if (USE_SDL_NET)
        find_library(SDL2_NET_LIBRARIES SDL2_net REQUIRED)
        target_link_libraries(pixelc ${SDL2_NET_LIBRARIES})
    endif ()
    if (USE_SDL_TTF)
        find_library(SDL2_TTF_LIBRARIES SDL2_ttf REQUIRED)
        target_link_libraries(pixelc ${SDL2_TTF_LIBRARIES})
    endif ()
    if (USE_FETCH)
        find_package(CURL REQUIRED)
        target_link_libraries(pixelc ${CURL_LIBRARIES})
    endif ()
endif ()


# mobile
if (PLATFORM_MOBILE)
    message("Setup Mobile")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-long-long -Wno-unused-function -Wno-unused-variable -Wno-missing-braces -Wno-unused-parameter -Wno-format-truncation")

    add_definitions(-DOPTION_GLES)
    add_definitions(-DOPTION_SDL)
    #add_definitions(-DOPTION_GYRO)
    add_definitions(-DM_NO_PRINT_COLOR)
    add_definitions(-DS_LOG_DO_NOT_USE_COLOR)
    add_definitions(-DS_LOG_DO_NOT_PRINT_TIME_FILE)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)


    find_library(GLES_LIB GLESv3 REQUIRED)

    target_link_libraries(pixelc
            m
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${GLES_LIB}
            )

    if (USE_SDL_MIXER)
        find_package(SDL2_mixer REQUIRED)
        target_link_libraries(pixelc ${SDL2_MIXER_LIBRARIES})
    endif ()
    if (USE_SDL_NET)
        find_package(SDL2_net REQUIRED)
        target_link_libraries(pixelc ${SDL2_NET_LIBRARIES})
    endif ()
    if (USE_SDL_TTF)
        find_package(SDL2_ttf REQUIRED)
        target_link_libraries(pixelc ${SDL2_TTF_LIBRARIES})
    endif ()
    if (USE_FETCH)
        find_package(CURL REQUIRED)
        target_link_libraries(pixelc ${CURL_LIBRARIES})
    endif ()
endif ()


# res
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (PLATFORM_MSVC)
    # also copy res to MSVC subdirs Debug and Release
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif()
