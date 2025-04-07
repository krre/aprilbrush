find_package(Qt6 REQUIRED COMPONENTS Test)

qt_add_executable(test_openraster tst_openraster.cpp)

target_link_libraries(test_openraster PRIVATE
    Qt6::Test
    common
)
