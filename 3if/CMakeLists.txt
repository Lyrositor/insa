# Allow the optional activation of the MAP ("mise au point") flag
option(TP-OO_MAP "Enable MAP (\"mise au point\") flag" OFF)
if (TP-OO_MAP)
    set_directory_properties(PROPERTIES
            DEFINITIONS -DMAP)
endif (TP-OO_MAP)

add_subdirectory(alg)
add_subdirectory(oo)
