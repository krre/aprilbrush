#pragma once
#include <QWidget>

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(const QSize& size);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
};
