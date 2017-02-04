
#include <QApplication>
#include <QtDebug>
#include <QIcon>
#include <QMainWindow>
#include <QMenuBar>

#include"mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();
}
