#include "layermanager.h"
#include <QtGui>

LayerManager::LayerManager(QWidget *parent) : QWidget(parent)
{        
    QBoxLayout *boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QListWidget *listWidget = new QListWidget;
    boxLayout->addWidget(listWidget);
    int buttonWidth = 40;

    QBoxLayout *buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QPushButton *addButton = new QPushButton(tr("Add"));
    addButton->setMaximumWidth(buttonWidth);
    buttonLayout->addWidget(addButton);

    QPushButton *upButton = new QPushButton(tr("Up"));
    upButton->setMaximumWidth(buttonWidth);
    buttonLayout->addWidget(upButton);

    QPushButton *downButton = new QPushButton(tr("Down"));
    downButton->setMaximumWidth(buttonWidth);
    buttonLayout->addWidget(downButton);

    QPushButton *mergeButton = new QPushButton(tr("Merge"));
    mergeButton->setMaximumWidth(buttonWidth);
    buttonLayout->addWidget(mergeButton);

    QPushButton *deleteButton = new QPushButton(tr("Delete"));
    deleteButton->setMaximumWidth(buttonWidth);
    buttonLayout->addWidget(deleteButton);

    boxLayout->addLayout(buttonLayout);

    setLayout(boxLayout);

}
