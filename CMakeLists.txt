cmake_minimum_required(VERSION 3.16)

project(xsd
    VERSION 4.2.0
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(FetchContent)

# FetchContent_Populate() is intentionally used because we only want
# to download dependency sources and compile their .cxx files as part
# of the xsd executable.
if(POLICY CMP0169)
    cmake_policy(SET CMP0169 OLD)
endif()


# ------------------------------------------------------------
# Sources
# ------------------------------------------------------------

# Do this BEFORE add_source_dependency(), because the helper
# appends fetched dependency sources to XSD_SOURCES.
file(GLOB_RECURSE XSD_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/xsd/xsd/*.cxx"
)

# Don't compile the pregenerated files through the normal source glob.
list(FILTER XSD_SOURCES EXCLUDE REGEX "/pregenerated/")



# ------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------

set(XSD_DEPENDENCY_LIBRARIES)
set(XSD_DEPENDENCY_INCLUDE_DIRS)

function(add_source_dependency PACKAGE_NAME GIT_REPOSITORY)
    find_package(${PACKAGE_NAME} CONFIG QUIET)

    if(${PACKAGE_NAME}_FOUND)
        message(STATUS "Found ${PACKAGE_NAME}")

        string(REGEX REPLACE "^lib" "" TARGET_NAME "${PACKAGE_NAME}")

        set(PACKAGE_TARGET
            "${PACKAGE_NAME}::${TARGET_NAME}"
        )

        if(TARGET "${PACKAGE_TARGET}")
            message(STATUS
                "Using ${PACKAGE_TARGET}"
            )

            list(APPEND XSD_DEPENDENCY_LIBRARIES
                "${PACKAGE_TARGET}"
            )

            set(XSD_DEPENDENCY_LIBRARIES
                "${XSD_DEPENDENCY_LIBRARIES}"
                PARENT_SCOPE
            )

            return()
        endif()
    endif()

    message(STATUS
        "${PACKAGE_NAME} not found, downloading sources..."
    )

    string(REPLACE "-" "_" FETCH_NAME "${PACKAGE_NAME}")

    FetchContent_Declare(
        ${FETCH_NAME}
        GIT_REPOSITORY "${GIT_REPOSITORY}"
    )

    FetchContent_GetProperties(${FETCH_NAME})

    if(NOT ${FETCH_NAME}_POPULATED)
        FetchContent_Populate(${FETCH_NAME})
    endif()

    # CodeSynthesis libraries keep their implementation sources
    # in the library source tree.
    file(GLOB_RECURSE DEPENDENCY_SOURCES
        CONFIGURE_DEPENDS
        "${${FETCH_NAME}_SOURCE_DIR}/${PACKAGE_NAME}/*.cxx"
    )

    if(NOT DEPENDENCY_SOURCES)
        message(FATAL_ERROR
            "No ${PACKAGE_NAME} .cxx source files found in "
            "${${FETCH_NAME}_SOURCE_DIR}"
        )
    endif()

    message(STATUS
        "${PACKAGE_NAME}: found ${DEPENDENCY_SOURCES}"
    )

    list(APPEND XSD_SOURCES
        ${DEPENDENCY_SOURCES}
    )

    list(APPEND XSD_DEPENDENCY_INCLUDE_DIRS
        "${${FETCH_NAME}_SOURCE_DIR}"
        "${${FETCH_NAME}_SOURCE_DIR}/${PACKAGE_NAME}"
    )

    set(XSD_SOURCES
        "${XSD_SOURCES}"
        PARENT_SCOPE
    )

    set(XSD_DEPENDENCY_INCLUDE_DIRS
        "${XSD_DEPENDENCY_INCLUDE_DIRS}"
        PARENT_SCOPE
    )
endfunction()

add_source_dependency(
    libcutl
    https://github.com/codesynthesis-com/libcutl.git
)

add_source_dependency(
    libxsd-frontend
    https://github.com/codesynthesis-com/libxsd-frontend.git
)

find_package(XercesC REQUIRED)


# ------------------------------------------------------------
# Version
# ------------------------------------------------------------

set(XSD_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(XSD_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(XSD_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(XSD_VERSION_STR  "${PROJECT_VERSION}")
set(XSD_VERSION_ID   "${PROJECT_VERSION}")
set(XSD_VERSION_FULL "${PROJECT_VERSION}")

# Final release.
set(XSD_PRE_RELEASE 0)
set(XSD_SNAPSHOT 0)
set(XSD_SNAPSHOT_ID "")

# Numeric version:
#
# AAAAA BBBBB CCCCC DDDE
#
# 5 digits major
# 5 digits minor
# 5 digits patch
# 3 digits pre-release/snapshot information
# 1 digit type
#
# Therefore:
#
# major * 10^14
# minor * 10^9
# patch * 10^4
#
math(EXPR XSD_VERSION_NUMBER
    "${XSD_VERSION_MAJOR} * 10000000000000"
)

math(EXPR XSD_VERSION_NUMBER
    "${XSD_VERSION_NUMBER} + ${XSD_VERSION_MINOR} * 100000000"
)

math(EXPR XSD_VERSION_NUMBER
    "${XSD_VERSION_NUMBER} + ${XSD_VERSION_PATCH} * 1000"
)

set(XSD_VERSION_HEADER
"// file      : xsd/version.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_VERSION

#define XSD_VERSION       ${XSD_VERSION_NUMBER}ULL
#define XSD_VERSION_STR   \"${XSD_VERSION_STR}\"
#define XSD_VERSION_ID    \"${XSD_VERSION_ID}\"
#define XSD_VERSION_FULL  \"${XSD_VERSION_FULL}\"

#define XSD_VERSION_MAJOR ${XSD_VERSION_MAJOR}
#define XSD_VERSION_MINOR ${XSD_VERSION_MINOR}
#define XSD_VERSION_PATCH ${XSD_VERSION_PATCH}

#define XSD_PRE_RELEASE   ${XSD_PRE_RELEASE}

#define XSD_SNAPSHOT      ${XSD_SNAPSHOT}ULL
#define XSD_SNAPSHOT_ID   \"${XSD_SNAPSHOT_ID}\"

#include <xercesc/util/XercesVersion.hpp>
#include <libcutl/version.hxx>
#include <libxsd-frontend/version.hxx>

#endif // XSD_VERSION
")

set(LIBXSD_VERSION_HEADER
"// file      : xsd/version.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_VERSION

#define LIBXSD_VERSION       ${XSD_VERSION_NUMBER}ULL
#define LIBXSD_VERSION_STR   \"${XSD_VERSION_STR}\"
#define LIBXSD_VERSION_ID    \"${XSD_VERSION_ID}\"
#define LIBXSD_VERSION_FULL  \"${XSD_VERSION_FULL}\"

#define LIBXSD_VERSION_MAJOR ${XSD_VERSION_MAJOR}
#define LIBXSD_VERSION_MINOR ${XSD_VERSION_MINOR}
#define LIBXSD_VERSION_PATCH ${XSD_VERSION_PATCH}

#define LIBXSD_PRE_RELEASE   ${XSD_PRE_RELEASE}

#define LIBXSD_SNAPSHOT      ${XSD_SNAPSHOT}ULL
#define LIBXSD_SNAPSHOT_ID   \"${XSD_SNAPSHOT_ID}\"

#endif // LIBXSD_VERSION
")

file(GENERATE
    OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/xsd/xsd/version.hxx"
    CONTENT
        "${XSD_VERSION_HEADER}"
)



file(GENERATE
    OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/libxsd/version.hxx"
    CONTENT
        "${LIBXSD_VERSION_HEADER}"
)


# ------------------------------------------------------------
# Pregenerated CLI sources
# ------------------------------------------------------------

set(XSD_PREGENERATED_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/xsd/xsd/pregenerated/xsd"
)

set(XSD_GENERATED_SOURCES
    "${XSD_PREGENERATED_DIR}/options.cxx"
    "${XSD_PREGENERATED_DIR}/cxx/options.cxx"
    "${XSD_PREGENERATED_DIR}/cxx/parser/options.cxx"
    "${XSD_PREGENERATED_DIR}/cxx/tree/options.cxx"
)

foreach(source IN LISTS XSD_GENERATED_SOURCES)
    if(NOT EXISTS "${source}")
        message(FATAL_ERROR
            "Missing pregenerated source: ${source}"
        )
    endif()
endforeach()


# ------------------------------------------------------------
# Executable
# ------------------------------------------------------------

add_executable(xsd
    ${XSD_SOURCES}
    ${XSD_GENERATED_SOURCES}
)

target_include_directories(xsd
    PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/xsd"
        "${CMAKE_CURRENT_SOURCE_DIR}/xsd"
        "${CMAKE_CURRENT_SOURCE_DIR}/xsd/xsd"
        "${CMAKE_CURRENT_SOURCE_DIR}/xsd/xsd/pregenerated"

        ${XSD_DEPENDENCY_INCLUDE_DIRS}
)

target_link_libraries(xsd
    PRIVATE
        ${XSD_DEPENDENCY_LIBRARIES}
        XercesC::XercesC
)

target_compile_features(xsd
    PRIVATE
        cxx_std_11
)


# ------------------------------------------------------------
# Build information
# ------------------------------------------------------------

set(XSD_COPYRIGHT
    "Copyright (c) 2005-2026 Code Synthesis Tools CC"
    CACHE STRING "XSD copyright notice"
)

target_compile_definitions(xsd
    PRIVATE
        XSD_COPYRIGHT="${XSD_COPYRIGHT}"
)

set_target_properties(xsd PROPERTIES
    OUTPUT_NAME xsdcxx
)


# ------------------------------------------------------------
# Installation
# ------------------------------------------------------------

# /usr/bin/xsdcxx
install(TARGETS xsd
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# /usr/include/xsd
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libxsd/xsd"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING
        PATTERN "*.hxx"
        PATTERN "*.ixx"
        PATTERN "*.txx"
        PATTERN "version.hxx" EXCLUDE
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/libxsd/version.hxx"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/xsd/cxx"
)

