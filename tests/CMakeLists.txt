if (test)
    add_executable(matrix_test matrix_test.cpp)
    add_test(matrix_gtests matrix_test)
    # include(FetchContent)

    # FetchContent_Declare(
    # googletest
    # GIT_REPOSITORY https://github.com/google/googletest.git
    # GIT_TAG        release-1.11.0
    # )

    # FetchContent_MakeAvailable(googletest)
    # add_library(GTest::GTest INTERFACE IMPORTED)
    # target_link_libraries(GTest::GTest INTERFACE gtest_main)

    # target_link_libraries(matrix_test
    #     PRIVATE matrix_multiplication
    #     GTest::GTest)
    


    target_link_libraries(matrix_test
        PRIVATE matrix::matrix_multiplication
        PRIVATE gtest
        PRIVATE gmock
        )

endif()