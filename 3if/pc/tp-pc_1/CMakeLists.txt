cmake_minimum_required(VERSION 3.0)
project(tp-pc_1 CXX)

# Set project properties
set(TP-PC1_BIN Parking)
set(TP-PC1_BIN_DIR bin)
set(TP-PC1_DEFINITIONS)
set(TP-PC1_FLAGS ${CC_COMMON_FLAGS} ${CXX_COMMON_FLAGS})
set(TP-PC1_INCLUDES include/)
set(TP-PC1_LINK lib/)
set(TP-PC1_MAIN src/Mere.cpp)
set(TP-PC1_SOURCES
        src/BarriereEntree.cpp
        src/BarriereSortie.cpp
        src/Simulateur.cpp src/Utils.cpp src/Config.cpp)

# Check if the MAP option is set
if (TP-PC_MAP)
    list(APPEND TP-PC1_DEFINITIONS -DMAP)
endif (TP-PC_MAP)

# Configure the executable's compilation
add_executable(${TP-PC1_BIN} ${TP-PC1_MAIN} ${TP-PC1_SOURCES})
set(TP-PC1_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-PC1_BIN_DIR})
set_target_properties(${TP-PC1_BIN} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-PC1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-PC1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-PC1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-PC1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-PC1_BIN_DIR_FULL})

# Link the required libraries
target_link_libraries(${TP-PC1_BIN} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libtp.a)

# Add flags and definitions
if (TP-PC1_DEFINITIONS)
    target_compile_definitions(${TP-PC1_BIN} PRIVATE ${TP-PC1_DEFINITIONS})
endif (TP-PC1_DEFINITIONS)
if (TP-PC1_FLAGS)
    target_compile_options(${TP-PC1_BIN} PRIVATE ${TP-PC1_FLAGS})
endif (TP-PC1_FLAGS)
if (TP-PC1_INCLUDES)
    include_directories(${TP-PC1_INCLUDES})
endif (TP-PC1_INCLUDES)
