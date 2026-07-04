cmake_minimum_required(VERSION 3.21)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum macOS version for deployment")

project ("macfanctl")

add_library(macfanctl STATIC)
target_include_directories(macfanctl PRIVATE "include")
target_compile_features(macfanctl PRIVATE c_std_17)

if(APPLE)
    find_library(COREFOUNDATION_LIB CoreFoundation FRAMEWORK REQUIRED)
    find_library(IOKIT_LIB  IOKit  FRAMEWORK REQUIRED)

    target_sources(macfanctl PRIVATE "src/libmacfanctl/impl/macos/macos_smc.c")

    target_link_libraries(macfanctl PRIVATE 
        ${COREFOUNDATION_LIB}
        ${IOKIT_LIB}
    )

    target_compile_options(macfanctl PRIVATE -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})
    target_link_options(macfanctl PRIVATE -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})
elseif(WIN32)
    target_sources(macfanctl PRIVATE "src/libmacfanctl/impl/win32/win32_smc.c")
endif()

# Daemon executable
add_executable(macfanctld "src/main.c" "src/config.c" "src/curve_point.c" "src/interpolate.c")

target_link_libraries(macfanctld PRIVATE macfanctl)

if(APPLE)
    target_compile_options(macfanctld PRIVATE -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})
    target_link_options(macfanctld PRIVATE -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})

    target_sources(macfanctld PRIVATE "src/impl/macos/macos_signal.c" "src/impl/macos/log/macos_log.c")
elseif(WIN32)
    target_sources(macfanctld PRIVATE "src/impl/win32/win32_signal.c" "src/impl/win32/log/win32_log.c")
endif()

#target_compile_options(macfanctld PRIVATE -ffunction-sections -fdata-sections)
#target_link_options(macfanctld PRIVATE -Wl,-s -Wl,-S)

target_compile_features(macfanctld PRIVATE c_std_17)

target_include_directories(macfanctld PRIVATE "include")
target_include_directories(macfanctld PRIVATE "src")