add_subdirectory(tp-oo_1)
add_subdirectory(tp-oo_2)
add_subdirectory(tp-oo_3)

option(TP-OO_MAP "Enable the MAP flag" OFF)
if(TP-OO_MAP)
    add_definitions(-DMAP)
endif(TP-OO_MAP)
