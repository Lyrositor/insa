add_subdirectory(tp-oo_1)
add_subdirectory(tp-oo_2)
add_subdirectory(tp-oo_3)

# Allow the optional activation of the MAP ("mise au point") flag
option(TP-OO_MAP "Enable MAP (\"mise au point\") flag" OFF)
if (TP-OO_MAP)
    set_directory_properties(PROPERTIES
        DEFINITIONS -DMAP)
endif (TP-OO_MAP)
