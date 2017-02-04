#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "editor.h"
#include "terminal.h"
#include "browser.h"
#include <QMainWindow>
#include <QAction>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createToolBar();
    void createMenuBar();
    void createWidgets();
    void createStatusBar();

    void newFile();
    void openfile();
    void save();
    void saveAs();
    void saveAll();
    void saveCopy();
    void closeFile();
    void closeAll();

    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void del();
    void selectall();


 public slots:
    void updateStatusBar(int l,int c);
private :
    Terminal *terminal;
    Editor *editor;
    Browser *browser;
    QLabel *lineLabel;
    QLabel *colLabel;
    QDockWidget *terminalDock;
    QDockWidget *browserDock;

  //  QAction *newAction;
    /*
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *saveAllAction;
    QAction *saveCopyAction;
    QAction *closeAction;
    QAction *closeAllAction;
    QAction *quitAction;

    QAction *undoAction;
    QAction *redoAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAllAction;
    QAction *prefAction;


    QAction *statusAction;
    QAction *browserAction;
    QAction *terminalAction;
    QAction *findAction;
    QAction *replaceAction;
    QAction *findNextAction;
    QAction *findPrevAction;
    QAction *goLineAction;


    QAction *fileStatAction;
    QAction *contentAction;
    QAction *aboutLineAction;
    QAction *aboutQtAction;
*/
};

#endif // MAINWINDOW_H
