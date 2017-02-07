
#include <QApplication>
#include <QtDebug>
#include <QIcon>
#include <QMainWindow>
#include <QMenuBar>

#include"mainwindow.h"
#include"kislabapp.h"

int main(int argc, char *argv[])
{
    //QApplication app(argc, argv);
     KISLabApp app(argc, argv);
   // QIcon::setThemeName("oxygen");
     app.setApplicationName("KISLab");
     app.setOrganizationDomain("www.github.com");
     app.setOrganizationName("OpenSource");
     app.setApplicationVersion("1.0.0");

    MainWindow mainWindow;

   mainWindow.show();


    return app.exec();
}
