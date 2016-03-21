add_subdirectory(tp-oo_1)
add_subdirectory(tp-oo_2)
add_subdirectory(tp-oo_3)
add_subdirectory(tp-oo_4)

# Allow the optional activation of the MAP ("mise au point") flag
option(TP-OO_MAP "Enable MAP (\"mise au point\") flag" OFF)
if (TP-OO_MAP)
    message(STATUS "Enabling MAP flag")
endif (TP-OO_MAP)
