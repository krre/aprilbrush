configure_file(config.h.in config.h @ONLY)

qt_add_library(common STATIC
    core/Application.cpp core/Application.h
    core/CommonTypes.h
    core/OpenRaster.cpp core/OpenRaster.h
    engine/BrushEngine.cpp engine/BrushEngine.h
    engine/Layer.cpp engine/Layer.h
    engine/undo/BrushCommand.cpp engine/undo/BrushCommand.h
    engine/undo/ClearCommand.cpp engine/undo/ClearCommand.h
    settings/FileSettings.h settings/FileSettings.cpp
    settings/Settings.cpp
    settings/Settings.h
    ui/BrushSettings.cpp ui/BrushSettings.h
    ui/BrushSlider.cpp ui/BrushSlider.h
    ui/Canvas.cpp ui/Canvas.h
    ui/CanvasTabWidget.cpp ui/CanvasTabWidget.h
    ui/ColorPicker.cpp ui/ColorPicker.h
    ui/InputDevice.cpp ui/InputDevice.h
    ui/MainWindow.cpp ui/MainWindow.h
    ui/dialog/NewImage.cpp ui/dialog/NewImage.h
    ui/dialog/Preferences.cpp ui/dialog/Preferences.h
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

target_link_libraries(common
    PUBLIC Qt6::Widgets
    PRIVATE Qt6::CorePrivate
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Qt6Gui_PRIVATE_INCLUDE_DIRS})
