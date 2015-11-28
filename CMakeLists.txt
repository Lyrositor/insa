cmake_minimum_required(VERSION 2.8)
project(insa)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(GNUCXX_COMMON_FLAGS "-Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused")

    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GNUCXX_COMMON_FLAGS})
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "-O3")
endif()

add_subdirectory(3if)
