set(SOURCES main.cpp)
add_executable(aprilbrush ${SOURCES})

target_link_libraries(aprilbrush PRIVATE
    Qt6::Widgets
    common
)
