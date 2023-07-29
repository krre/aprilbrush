#pragma once
#include <QPixmap>
#include <QSize>
#include <QPoint>

class Layer {
public:
    Layer(const QString& name, const QSize& size);

    void setName(const QString& name);
    const QString& name() const;

    QSize size() const;

    QPixmap* pixmap();
    void setPixmap(const QPixmap& pixmap);

    void clear();

    void setVisible(bool visible);
    bool isVisible() const;

    void setLocked(bool locked);
    bool isLocked() const;

    void setSelected(bool selected);
    bool isSelected() const;

private:
    QString m_name;
    QPixmap m_pixmap;
    bool m_visible = true;
    bool m_locked = false;
    bool m_selected = false;
};
