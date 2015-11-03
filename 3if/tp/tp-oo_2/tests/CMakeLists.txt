include_directories(../src)

set(TP-OO_2_TEST_MAIN main.cpp)

add_executable(tp-oo_2-test ${TP-OO_2_TEST_MAIN})
target_link_libraries(tp-oo_2-test tp-oo_2-lib)
add_dependencies(tp-oo_2-test tp-oo_2-lib)