/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PicWidget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pLastButton;
    QGraphicsView *m_pPicView;
    QPushButton *m_pNextButton;

    void setupUi(QWidget *PicWidget)
    {
        if (PicWidget->objectName().isEmpty())
            PicWidget->setObjectName(QStringLiteral("PicWidget"));
        PicWidget->resize(843, 658);
        horizontalLayoutWidget = new QWidget(PicWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 8, 831, 441));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_pLastButton = new QPushButton(horizontalLayoutWidget);
        m_pLastButton->setObjectName(QStringLiteral("m_pLastButton"));

        horizontalLayout->addWidget(m_pLastButton);

        m_pPicView = new QGraphicsView(horizontalLayoutWidget);
        m_pPicView->setObjectName(QStringLiteral("m_pPicView"));

        horizontalLayout->addWidget(m_pPicView);

        m_pNextButton = new QPushButton(horizontalLayoutWidget);
        m_pNextButton->setObjectName(QStringLiteral("m_pNextButton"));

        horizontalLayout->addWidget(m_pNextButton);


        retranslateUi(PicWidget);

        QMetaObject::connectSlotsByName(PicWidget);
    } // setupUi

    void retranslateUi(QWidget *PicWidget)
    {
        PicWidget->setWindowTitle(QApplication::translate("PicWidget", "Form", Q_NULLPTR));
        m_pLastButton->setText(QApplication::translate("PicWidget", "PushButton", Q_NULLPTR));
        m_pNextButton->setText(QApplication::translate("PicWidget", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PicWidget: public Ui_PicWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
