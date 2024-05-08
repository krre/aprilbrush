cmake_minimum_required(VERSION 3.22)

project(aprilbrush VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    LinguistTools
)

qt_standard_project_setup()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)

SET(TS_SOURCE src/i18n/aprilbrush-ru.ts)

qt_add_translations(aprilbrush
    TS_FILES ${TS_SOURCE}
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(other
    SOURCES
    ${TS_SOURCE}
    README.md
)
