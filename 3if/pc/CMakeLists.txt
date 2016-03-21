add_subdirectory(tp-pc_1)

# Allow the optional activation of the MAP ("mise au point") flag
option(TP-PC_MAP "Enable MAP (\"mise au point\") flag" OFF)
if (TP-PC_MAP)
    message(STATUS "Enabling MAP flag")
endif (TP-PC_MAP)
