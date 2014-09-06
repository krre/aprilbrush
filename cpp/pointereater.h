#ifndef POINTEREATER_H
#define POINTEREATER_H

#include <QObject>

class PointerEater : public QObject
{
    Q_OBJECT
public:
    explicit PointerEater(QObject *parent = 0);

signals:
    void pressure(qreal pressure);
    void pressed(int type); // 0 - mouse, 1 - tablet

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // POINTEREATER_H
