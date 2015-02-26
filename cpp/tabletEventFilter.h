#ifndef TabletEventFilter_H
#define TabletEventFilter_H

#include <QObject>

class TabletEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit TabletEventFilter(QObject *parent = 0);

signals:
    void pressure(qreal pressure);
    void pressed(int type); // 0 - mouse, 1 - tablet

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // TabletEventFilter_H
