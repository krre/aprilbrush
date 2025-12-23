cmake_minimum_required(VERSION 3.30)

project(aprilbrush VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
set(REQUIRED_QT_VERSION 6.10.0)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API ON)

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS
    Widgets
    LinguistTools
    CorePrivate
)

qt_standard_project_setup(
    REQUIRES ${REQUIRED_QT_VERSION}
    I18N_TRANSLATED_LANGUAGES ru
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)

qt_add_translations(${PROJECT_NAME}
    NO_GENERATE_PLURALS_TS_FILE
    TS_OUTPUT_DIRECTORY i18n
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(other
    SOURCES
    README.md
)
