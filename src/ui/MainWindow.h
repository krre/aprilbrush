#pragma once
#include <QMainWindow>

class FileSettings;
class CanvasTabWidget;
class Canvas;
class ColorPicker;
class BrushEngine;
class EventFilter;
class QUndoGroup;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createNew();
    void open();
    void save();
    void saveAs();
    void exportImage();

    void clear();

    void showAbout();
    void showPreferences();
    void showInputDevice();

private:
    void readSettings();
    void writeSettings();

    void createActions();
    void createUi();
    void createDockWindows();
    void applyHotSettings();

    QScopedPointer<FileSettings> m_fileSettings;

    Canvas* currentCanvas() const;

    CanvasTabWidget* m_canvasTabWidget;
    ColorPicker* m_colorPicker = nullptr;
    BrushEngine* m_brushEngine = nullptr;
    QMenu* m_viewMenu = nullptr;
    QUndoGroup* m_undoGroup = nullptr;
};
