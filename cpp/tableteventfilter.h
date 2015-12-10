#pragma once
#include <QtCore>

class TabletEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit TabletEventFilter() {}

signals:
    void action(QVariantMap event);

public slots:

protected:
    bool eventFilter(QObject* obj, QEvent* event);

};
