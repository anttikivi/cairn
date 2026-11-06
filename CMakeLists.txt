# SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.18.0)
project(cairn LANGUAGES C)

include(CTest)
include(GNUInstallDirs)

option(CAIRN_DEVELOPER_TOOLS "Enable targets for formatting and linting" OFF)
option(
    CAIRN_ENABLE_CLANG_FORMAT
    "When developer tooling is enabled, enable the formatting and linting targets the use clang-format"
    ON)
option(CAIRN_ENABLE_CLANG_TIDY
       "When developer tooling is enabled, enable the linting targets that use clang-tidy" ON)
option(CAIRN_ENABLE_UVX
       "When developer tooling is enabled, enable the formatting and linting targets that use uvx"
       ON)
option(CAIRN_INSTALL "Generate install rules" OFF)
option(CAIRN_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "Debug"
        CACHE STRING "Build configuration" FORCE)
endif()

function(cairn_configure_target target)
    set_target_properties(
        "${target}"
        PROPERTIES C_STANDARD 99
                   C_STANDARD_REQUIRED ON
                   C_EXTENSIONS OFF)

    if(MSVC OR CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        target_compile_options("${target}" PRIVATE /W4)

        if(CAIRN_WARNINGS_AS_ERRORS)
            target_compile_options("${target}" PRIVATE /WX)
        endif()
    elseif(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
        target_compile_options(
            "${target}"
            PRIVATE -Wall
                    -Wextra
                    -Wpedantic
                    -Wshadow
                    -Wundef
                    -Wunused
                    -Wnull-dereference
                    -Wredundant-decls
                    -Wconversion
                    -Wsign-conversion
                    -Wdouble-promotion
                    -Wcast-align
                    -Wcast-qual
                    -Wwrite-strings
                    -Wstrict-prototypes
                    -Wmissing-prototypes
                    -Wmissing-declarations
                    -Wdeclaration-after-statement
                    -Wold-style-definition
                    -Wformat=2
                    -Wvla)

        if(CAIRN_WARNINGS_AS_ERRORS)
            target_compile_options("${target}" PRIVATE -Werror)
        endif()

        if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
            target_compile_options(
                "${target}"
                PRIVATE -Wformat-overflow=2
                        -Wformat-truncation=2
                        -Wlogical-op
                        -Wduplicated-cond
                        -Wduplicated-branches
                        -Wrestrict
                        -Wjump-misses-init
                        -Wstack-usage=8192)
        else()
            target_compile_options("${target}" PRIVATE -Wdocumentation)
        endif()
    elseif(CMAKE_C_COMPILER_ID STREQUAL "TinyCC")
        target_compile_options("${target}" PRIVATE -Wall)
    endif()
endfunction()

set(CAIRN_SOURCES src/buffer.c src/debug.c src/io.c src/semver.c src/strings.c src/test.c)
set(CAIRN_INCLUDES
    include/cairn/buffer.h
    include/cairn/debug.h
    include/cairn/error.h
    include/cairn/io.h
    include/cairn/semver.h
    include/cairn/strings.h
    include/cairn/test.h
    include/cairn/units.h)

add_library(cairn STATIC ${CAIRN_SOURCES})
cairn_configure_target(cairn)

add_library(cairn::cairn ALIAS cairn)

target_include_directories(cairn PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                                        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(CAIRN_INSTALL)
    include(CMakePackageConfigHelpers)

    set(CAIRN_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/cairn")

    install(
        TARGETS cairn
        EXPORT cairnTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

    install(FILES ${CAIRN_INCLUDES} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/cairn")

    install(
        EXPORT cairnTargets
        FILE cairnTargets.cmake
        NAMESPACE cairn::
        DESTINATION "${CAIRN_INSTALL_CMAKEDIR}")

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cairnConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cairnConfig.cmake"
        INSTALL_DESTINATION "${CAIRN_INSTALL_CMAKEDIR}")

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cairnConfig.cmake"
            DESTINATION "${CAIRN_INSTALL_CMAKEDIR}")
endif()

if(BUILD_TESTING)
    set(CAIRN_TESTS buffer strings)

    add_library(cairn_test STATIC ${CAIRN_SOURCES})
    cairn_configure_target(cairn_test)
    target_include_directories(cairn_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_compile_definitions(cairn_test PRIVATE CAIRN_BUFFER_ALLOW_APPEND_INT=1)

    foreach(test_name IN LISTS CAIRN_TESTS)
        string(REPLACE "/" "_" test_id "${test_name}")
        set(test_target "test_${test_id}")

        add_executable("${test_target}" "test/${test_name}.c")
        cairn_configure_target("${test_target}")
        target_compile_definitions("${test_target}" PRIVATE CAIRN_BUFFER_ALLOW_APPEND_INT=1)
        target_link_libraries("${test_target}" PRIVATE cairn_test)

        add_test(NAME "${test_name}" COMMAND "${test_target}")
    endforeach()
endif()

if(CAIRN_DEVELOPER_TOOLS)
    if(CAIRN_ENABLE_CLANG_TIDY AND NOT CMAKE_GENERATOR MATCHES "Ninja|Makefiles")
        message(FATAL_ERROR "Developer tooling requires a Ninja or Makefiles generator to generate "
                            "compile_commands.json")
    endif()

    add_custom_target(annotate)
    add_custom_target(format)
    add_custom_target(lint)

    file(
        GLOB_RECURSE
        CAIRN_CLANG_FORMAT_FILES
        CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/include/cairn/*.c"
        "${PROJECT_SOURCE_DIR}/include/cairn/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.h"
        "${PROJECT_SOURCE_DIR}/test/*.c"
        "${PROJECT_SOURCE_DIR}/test/*.h")
    file(GLOB_RECURSE CAIRN_CLANG_TIDY_FILES CONFIGURE_DEPENDS
         "${PROJECT_SOURCE_DIR}/include/cairn/*.c" "${PROJECT_SOURCE_DIR}/src/*.c")

    if(CAIRN_ENABLE_CLANG_FORMAT)
        find_program(CAIRN_CLANG_FORMAT NAMES clang-format REQUIRED)
        add_custom_target(
            clang-format
            COMMAND "${CAIRN_CLANG_FORMAT}" "-i" ${CAIRN_CLANG_FORMAT_FILES}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            VERBATIM)
        add_custom_target(
            clang-format-check
            COMMAND "${CAIRN_CLANG_FORMAT}" "--dry-run" "--Werror" ${CAIRN_CLANG_FORMAT_FILES}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            VERBATIM)
        add_dependencies(format clang-format)
        add_dependencies(lint clang-format-check)
    endif()

    if(CAIRN_ENABLE_CLANG_TIDY)
        find_program(CAIRN_CLANG_TIDY NAMES clang-tidy REQUIRED)
        add_custom_target(
            clang-tidy
            COMMAND "${CAIRN_CLANG_TIDY}" "-p=${CMAKE_BINARY_DIR}" ${CAIRN_CLANG_TIDY_FILES}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            VERBATIM)
        add_dependencies(lint clang-tidy)
    endif()

    if(CAIRN_ENABLE_UVX)
        find_program(CAIRN_UVX NAMES uvx REQUIRED)
        add_custom_target(
            reuse-annotate
            COMMAND
                "${CAIRN_UVX}" "--from=reuse[charset-normalizer]" "reuse" "annotate"
                "--copyright=Antti Kivi <antti@anttikivi.com>" "--license=LGPL-3.0-or-later"
                "--copyright-prefix=spdx-c" CMakeLists.txt ${CAIRN_CLANG_FORMAT_FILES}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            VERBATIM)
        add_custom_target(
            reuse-check
            COMMAND "${CAIRN_UVX}" "--from=reuse[charset-normalizer]" "reuse" "lint"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            VERBATIM)
        add_dependencies(annotate reuse-annotate)
        add_dependencies(lint reuse-check)
    endif()
endif()
