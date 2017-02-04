/********************************************************************************
** Form generated from reading UI file 'SearchBar.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHBAR_H
#define UI_SEARCHBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchBar
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *closeButton;
    QLabel *findLabel;
    QLineEdit *searchTextEdit;
    QToolButton *findPreviousButton;
    QToolButton *findNextButton;
    QToolButton *optionsButton;

    void setupUi(QWidget *SearchBar)
    {
        if (SearchBar->objectName().isEmpty())
            SearchBar->setObjectName(QStringLiteral("SearchBar"));
        SearchBar->resize(399, 40);
        horizontalLayout = new QHBoxLayout(SearchBar);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        closeButton = new QToolButton(SearchBar);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("dialog-close");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        closeButton->setIcon(icon);

        horizontalLayout->addWidget(closeButton);

        findLabel = new QLabel(SearchBar);
        findLabel->setObjectName(QStringLiteral("findLabel"));

        horizontalLayout->addWidget(findLabel);

        searchTextEdit = new QLineEdit(SearchBar);
        searchTextEdit->setObjectName(QStringLiteral("searchTextEdit"));

        horizontalLayout->addWidget(searchTextEdit);

        findPreviousButton = new QToolButton(SearchBar);
        findPreviousButton->setObjectName(QStringLiteral("findPreviousButton"));
        QIcon icon1;
        iconThemeName = QStringLiteral("go-previous");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        findPreviousButton->setIcon(icon1);

        horizontalLayout->addWidget(findPreviousButton);

        findNextButton = new QToolButton(SearchBar);
        findNextButton->setObjectName(QStringLiteral("findNextButton"));
        QIcon icon2;
        iconThemeName = QStringLiteral("go-next");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        findNextButton->setIcon(icon2);

        horizontalLayout->addWidget(findNextButton);

        optionsButton = new QToolButton(SearchBar);
        optionsButton->setObjectName(QStringLiteral("optionsButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(""), QSize(), QIcon::Normal, QIcon::Off);
        optionsButton->setIcon(icon3);
        optionsButton->setPopupMode(QToolButton::InstantPopup);
        optionsButton->setArrowType(Qt::DownArrow);

        horizontalLayout->addWidget(optionsButton);


        retranslateUi(SearchBar);

        QMetaObject::connectSlotsByName(SearchBar);
    } // setupUi

    void retranslateUi(QWidget *SearchBar)
    {
        SearchBar->setWindowTitle(QApplication::translate("SearchBar", "SearchBar", 0));
        closeButton->setText(QApplication::translate("SearchBar", "X", 0));
        findLabel->setText(QApplication::translate("SearchBar", "Find:", 0));
        findPreviousButton->setText(QApplication::translate("SearchBar", "<", 0));
        findNextButton->setText(QApplication::translate("SearchBar", ">", 0));
        optionsButton->setText(QApplication::translate("SearchBar", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchBar: public Ui_SearchBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHBAR_H
