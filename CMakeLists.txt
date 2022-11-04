cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(otus_sparse_matrix VERSION ${PROJECT_VESRION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  " ${CMAKE_CXX_FLAGS_INIT} -std=c++17 -fPIC")
message( "CMAKE_BINARY_DIR : " ${CMAKE_BINARY_DIR} )

include_directories(SYSTEM ./include)
include_directories(SYSTEM ./src)

# add source files
file(GLOB SOURCES "src/*.tpp")

add_executable(${PROJECT_NAME} main.cpp)

find_package(GTest REQUIRED)
add_executable(test_sparse_matrix tests/test_sparse_matrix.cpp)
target_include_directories(test_sparse_matrix
        PRIVATE
        "${CMAKE_BINARY_DIR}"
        "${CMAKE_HOME_DIRECTORY}"
        "${GTEST_INCLUDE_DIR}"
        )
target_link_libraries(test_sparse_matrix
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
    target_compile_options(test_sparse_matrix PRIVATE
            /W4)

else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(test_sparse_matrix PRIVATE
            -Wall -Wextra -pedantic -Werror
            )

endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT shirkin39@mail.ru)
include(CPack)

enable_testing()
add_test(test_sparse_matrix test_sparse_matrix)