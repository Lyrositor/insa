cmake_minimum_required(VERSION 2.8.4)
project(insa)

# Set the default output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
endforeach (OUTPUTCONFIG)

# Set the common compiler flags
if (CMAKE_COMPILER_IS_GNUCC)
    set(CC_COMMON_FLAGS
            -Wall
            -Wcast-align
            -Wcast-qual
            -Wctor-dtor-privacy
            -Wdisabled-optimization
            -Wextra
            -Wformat=2
            -Winit-self
            -Wlogical-op
            -Wmissing-declarations
            -Wmissing-include-dirs
            -Wnoexcept
            -Wold-style-cast
            -Woverloaded-virtual
            -Wredundant-decls
            -Wshadow
            -Wsign-conversion
            -Wsign-promo
            -Wstrict-null-sentinel
            -Wstrict-overflow=5
            -Wswitch-default
            -Wundef)
elseif (MSVC)
    set(CC_COMMON_FLAGS /W4)
endif (CMAKE_COMPILER_IS_GNUCC)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CXX_COMMON_FLAGS
            -Wctor-dtor-privacy
            -Wnoexcept
            -Wold-style-cast
            -Woverloaded-virtual
            -Wsign-promo
            -Wstrict-null-sentinel)
endif (CMAKE_COMPILER_IS_GNUCXX)

# Define a function for automatic generation of a simpler makefile
function (create_makefile
        FILENAME BIN BUILD SRC_ MAIN CXXFLAGS_ DEFINITIONS_ INCLUDE_ LIBS
        WORKING_DIR)
    message(STATUS "Creating makefile for ${BIN}")

    file(READ ${CMAKE_SOURCE_DIR}/common/makefile.in MAKEFILE)
    file(READ ${CMAKE_SOURCE_DIR}/common/makefile-target.in TARGET_TEMPLATE)

    string(REPLACE ";" " " SRC "${SRC_}")

    list(APPEND CXXFLAGS_ ${GNUCC_COMMON_FLAGS})
    list(APPEND CXXFLAGS_ ${GNUCXX_COMMON_FLAGS})
    list(REMOVE_DUPLICATES CXXFLAGS_)
    list(SORT CXXFLAGS_)
    string(REPLACE ";" " " CXXFLAGS "${CXXFLAGS_}")

    list(APPEND DEFINITIONS_ "-DNDEBUG")
    list(REMOVE_DUPLICATES DEFINITIONS_)
    list(SORT DEFINITIONS_)
    string(REPLACE ";" " " DEFINITIONS "${DEFINITIONS_}")

    foreach (INC ${INCLUDE_})
        string(REPLACE ${INC} "$(INCFLAG)${INC} " I_INC ${INC})
        string(CONCAT INCLUDE ${I_INC})
    endforeach (INC)

    string(CONFIGURE ${MAKEFILE} MAKEFILE @ONLY)

    foreach (CPP ${SRC_})
        string(REPLACE ".cpp" ".o" OBJ ${CPP})
        string(REPLACE ".cpp" ".h" H ${CPP})
        string(CONFIGURE ${TARGET_TEMPLATE} TARGET)
        string(CONCAT MAKEFILE ${MAKEFILE} ${TARGET})
    endforeach (CPP)

    file(WRITE ${FILENAME} ${MAKEFILE})

    add_custom_target(${BIN}-make
            COMMAND make
            WORKING_DIRECTORY ${WORKING_DIR})
endfunction (create_makefile)

add_subdirectory(3if)
