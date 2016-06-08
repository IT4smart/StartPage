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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QLabel *lblMessage;
    QLabel *lblLayoutContainer;
    QLabel *lblUser;
    QLabel *lblPW;
    QLineEdit *leUser;
    QLineEdit *lePW;
    QPushButton *btnLogin;

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
        tbtnNetStatus->setFocusPolicy(Qt::NoFocus);
        lblMessage = new QLabel(centralwidget);
        lblMessage->setObjectName(QStringLiteral("lblMessage"));
        lblMessage->setGeometry(QRect(327, 480, 481, 31));
        lblMessage->setFont(font);
        lblMessage->setAlignment(Qt::AlignCenter);
        lblLayoutContainer = new QLabel(centralwidget);
        lblLayoutContainer->setObjectName(QStringLiteral("lblLayoutContainer"));
        lblLayoutContainer->setGeometry(QRect(250, 110, 651, 91));
        lblLayoutContainer->setFont(font);
        lblLayoutContainer->setAlignment(Qt::AlignCenter);
        lblUser = new QLabel(centralwidget);
        lblUser->setObjectName(QStringLiteral("lblUser"));
        lblUser->setGeometry(QRect(239, 219, 121, 17));
        lblUser->setFont(font);
        lblPW = new QLabel(centralwidget);
        lblPW->setObjectName(QStringLiteral("lblPW"));
        lblPW->setGeometry(QRect(240, 280, 111, 17));
        lblPW->setFont(font);
        leUser = new QLineEdit(centralwidget);
        leUser->setObjectName(QStringLiteral("leUser"));
        leUser->setGeometry(QRect(400, 210, 371, 31));
        leUser->setFont(font);
        lePW = new QLineEdit(centralwidget);
        lePW->setObjectName(QStringLiteral("lePW"));
        lePW->setGeometry(QRect(400, 270, 371, 31));
        lePW->setFont(font);
        lePW->setEchoMode(QLineEdit::Password);
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(510, 340, 141, 41));
        btnLogin->setFont(font);
        btnLogin->setAutoDefault(true);
        StartPage->setCentralWidget(centralwidget);

        retranslateUi(StartPage);

        btnLogin->setDefault(false);


        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QMainWindow *StartPage)
    {
        StartPage->setWindowTitle(QApplication::translate("StartPage", "MainWindow", 0));
        lblLogo->setText(QApplication::translate("StartPage", "lblLogo", 0));
        lblClock->setText(QApplication::translate("StartPage", "lblClock", 0));
        tbtnNetStatus->setText(QApplication::translate("StartPage", "tbtnNetStatus", 0));
        lblMessage->setText(QApplication::translate("StartPage", "lblMessage", 0));
        lblLayoutContainer->setText(QApplication::translate("StartPage", "lblLayoutContainer", 0));
        lblUser->setText(QApplication::translate("StartPage", "lblUser", 0));
        lblPW->setText(QApplication::translate("StartPage", "lblPW", 0));
        btnLogin->setText(QApplication::translate("StartPage", "btnLogin", 0));
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
