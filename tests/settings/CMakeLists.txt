qt_add_executable(test_settings tst_preferences.cpp)

target_link_libraries(test_settings PRIVATE
    Qt6::Test
    common
    test_common
)
