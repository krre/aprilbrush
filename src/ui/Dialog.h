#pragma once
#include <QDialog>

class QLayout;
class QDialogButtonBox;

class Dialog : public QDialog {
public:
    Dialog(QWidget* parent);

    QDialogButtonBox* buttonBox() const;
    void setContentWidget(QWidget* contentWidget, bool stretchAfter = true);
    void setContentLayout(QLayout* contentLayout, bool stretchAfter = true);
    void resizeToWidth(int width);

private:
    QDialogButtonBox* m_buttonBox = nullptr;
};
