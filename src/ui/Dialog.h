#pragma once
#include <QDialog>

class QLayout;
class QDialogButtonBox;

class Dialog : public QDialog {
public:
    Dialog(QWidget* parent);

    QDialogButtonBox* buttonBox() const;
    void resizeToWidth(int width);

    void setContentWidget(QWidget* contentWidget, bool stretchAfter = true);
    void setContentLayout(QLayout* contentLayout, bool stretchAfter = true);

private:
    QDialogButtonBox* m_buttonBox = nullptr;
};
