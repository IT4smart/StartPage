/********************************************************************************
** Form generated from reading UI file 'startpage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTPAGE_H
#define UI_STARTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartPage
{
public:
    QWidget *centralwidget;
    QLabel *lblLogo;
    QLabel *lblClock;
    QToolButton *tbtnNetStatus;
    QToolButton *tbtnLogin;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartPage)
    {
        if (StartPage->objectName().isEmpty())
            StartPage->setObjectName(QStringLiteral("StartPage"));
        StartPage->resize(1920, 1080);
        centralwidget = new QWidget(StartPage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lblLogo = new QLabel(centralwidget);
        lblLogo->setObjectName(QStringLiteral("lblLogo"));
        lblLogo->setGeometry(QRect(40, 30, 150, 150));
        QFont font;
        font.setPointSize(18);
        lblLogo->setFont(font);
        lblClock = new QLabel(centralwidget);
        lblClock->setObjectName(QStringLiteral("lblClock"));
        lblClock->setGeometry(QRect(40, 460, 200, 51));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblClock->sizePolicy().hasHeightForWidth());
        lblClock->setSizePolicy(sizePolicy);
        lblClock->setFont(font);
        lblClock->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        tbtnNetStatus = new QToolButton(centralwidget);
        tbtnNetStatus->setObjectName(QStringLiteral("tbtnNetStatus"));
        tbtnNetStatus->setGeometry(QRect(940, 470, 191, 51));
        tbtnNetStatus->setFont(font);
        tbtnLogin = new QToolButton(centralwidget);
        tbtnLogin->setObjectName(QStringLiteral("tbtnLogin"));
        tbtnLogin->setGeometry(QRect(500, 230, 131, 111));
        tbtnLogin->setFont(font);
        StartPage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartPage);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 25));
        StartPage->setMenuBar(menubar);
        statusbar = new QStatusBar(StartPage);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        StartPage->setStatusBar(statusbar);

        retranslateUi(StartPage);

        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QMainWindow *StartPage)
    {
        StartPage->setWindowTitle(QApplication::translate("StartPage", "MainWindow", 0));
        lblLogo->setText(QApplication::translate("StartPage", "lblLogo", 0));
        lblClock->setText(QApplication::translate("StartPage", "lblClock", 0));
        tbtnNetStatus->setText(QApplication::translate("StartPage", "tbtnNetStatus", 0));
        tbtnLogin->setText(QApplication::translate("StartPage", "tbtnLogin", 0));
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
