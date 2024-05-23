cmake_minimum_required(VERSION 3.27)
project(procmaps)

set(CMAKE_CXX_STANDARD 17)
set(ANTLR_TAG 4.13.1)

find_package(antlr4-generator REQUIRED)
find_package(antlr4-runtime REQUIRED)

set(ANTLR4_JAR_LOCATION "${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-${ANTLR_TAG}-complete.jar")
if(NOT EXISTS "${ANTLR4_JAR_LOCATION}")
    file(
        DOWNLOAD
        "https://www.antlr.org/download/antlr-${ANTLR_TAG}-complete.jar"
        "${ANTLR4_JAR_LOCATION}"
    )
endif()

antlr4_generate(
    procmaps
    ${CMAKE_SOURCE_DIR}/ProcMaps.g4
    BOTH
)

include_directories(
    ${ANTLR4_INCLUDE_DIR_procmaps}
    ${ANTLR4_INCLUDE_DIR}
)

add_executable(procmaps
    main.cpp
    ${ANTLR4_SRC_FILES_procmaps}
)

add_dependencies(procmaps antlr4_static)
target_link_libraries(procmaps PRIVATE antlr4_static)

