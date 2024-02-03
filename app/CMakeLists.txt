add_executable(aprilbrush main.cpp)

target_link_libraries(aprilbrush PRIVATE
    Qt6::Widgets
    common
)
