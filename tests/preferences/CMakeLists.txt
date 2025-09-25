qt_add_executable(test_preferences TestPreferences.cpp)

target_link_libraries(test_preferences PRIVATE
    Qt6::Test
    common
    test_common
)
