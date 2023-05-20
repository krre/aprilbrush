#pragma once
#include <QPixmap>
#include <QSize>
#include <QPoint>

class QPixmap;

class Layer {
public:
    Layer(const QString& name, const QSize& size);

    void setName(const QString& name);
    const QString& name() const;

    const QSize& size() const;
    void setSize(QSize size);

    QPixmap* pixmap();
    void setPixmap(const QPixmap& pixmap);

    QByteArray data() const;
    void setData(QByteArray& data);

    void clear();

    QByteArray image(const QPoint& topLeft = QPoint(), const QPoint& bottomRight = QPoint());
    void setImage(const QByteArray& image, const QPoint& topLeft = QPoint());

    void setVisible(bool visible);
    bool isVisible() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setSelected(bool selected);
    bool isSelected() const;

private:
    QString m_name;
    QSize m_size;
    QPixmap m_pixmap;
    bool m_visible = true;
    bool m_locked = false;
    bool m_selected = false;
};
