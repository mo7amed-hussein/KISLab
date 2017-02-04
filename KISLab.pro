
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = KISLab
TEMPLATE = app

DESTDIR = ./build

INCLUDEPATH += ./include \
		./external/qtermwidget/lib \
		./external/QScintilla/Qt4Qt5

#DEPENDPATH=./include

OBJECTS_DIR= ./obj
MOC_DIR = ./moc 

LIBS += -L./external/QScintilla/Qt4Qt5/ -lqscintilla2

LIBS += -L./external/qtermwidget/build/ -lqtermwidget5

SOURCES += src/main.cpp \
            src/mainwindow.cpp \
            src/terminal.cpp \
            src/browser.cpp \
            src/editor.cpp

HEADERS += include/mainwindow.h \
           include/terminal.h \
           include/browser.h \
           include/editor.h

RESOURCES += \
    resources/application.qrc



