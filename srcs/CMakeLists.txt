project(matrix_multiplication)

add_library(${PROJECT_NAME} STATIC
    matrix_multiplication.cpp
)

add_library(matrix::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/includes)