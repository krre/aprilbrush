configure_file(config.h.in config.h @ONLY)

add_library(common STATIC
    core/Application.cpp core/Application.h
    core/CommonTypes.h
    core/OpenRaster.cpp core/OpenRaster.h
    engine/undo/BrushCommand.cpp engine/undo/BrushCommand.h
    engine/undo/ClearCommand.cpp engine/undo/ClearCommand.h
    engine/BrushEngine.cpp engine/BrushEngine.h
    engine/Layer.cpp engine/Layer.h
    ui/BrushSettings.cpp ui/BrushSettings.h
    ui/BrushSlider.cpp ui/BrushSlider.h
    ui/Canvas.cpp ui/Canvas.h
    ui/CanvasTabWidget.cpp ui/CanvasTabWidget.h
    ui/ColorPicker.cpp ui/ColorPicker.h
    ui/InputDevice.cpp ui/InputDevice.h
    ui/MainWindow.cpp ui/MainWindow.h
    ui/NewImage.cpp ui/NewImage.h
    ui/Preferences.cpp ui/Preferences.h
    ui/StandardDialog.cpp ui/StandardDialog.h
    i18n/aprilbrush-ru.ts
    settings/Settings.h
    settings/FileSettings.h settings/FileSettings.cpp
)

SET(TS_SOURCE i18n/aprilbrush-ru.ts)

qt_add_translations(common TS_FILES ${TS_SOURCE})

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    ${TS_SOURCE}
    config.h.in
)

target_link_libraries(common PRIVATE Qt6::Widgets )
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Qt6Gui_PRIVATE_INCLUDE_DIRS})
