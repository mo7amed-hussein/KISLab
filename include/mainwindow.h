#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "editor.h"
#include "terminal.h"
#include "browser.h"
#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include<QEvent>
#include <finddialog.h>
#include<aboutdialog.h>
#define MAX_RECENT_FILES  6

struct RecentFile{
    QString filePath;
};

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

    void find();
    void quitApp();
    void checkClipboard();
    void about();

    void readSetting();
    void saveSetting();


 public slots:
    void updateStatusBar(int l,int c);
    void toggleStatusbar();
    void goLineSlot();
    void toLowerSlot();
    void toUpperSlot();
    void timeStampSlot();
    void copyFileName();
    void copyFullPath();
    void copyDir();
    void fileStatSlot();
    void checkCopy(bool b);
    void fileChangedSlot(bool s);
    void openRecent();
    void createRecentfilesActions();

 protected:

   virtual bool event(QEvent * event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void closeEvent(QCloseEvent * event);

private :
    Terminal *terminal;
    Editor *editor;
    Browser *browser;
    QLabel *lineLabel;

    QDockWidget *terminalDock;
    QDockWidget *browserDock;
    FindDialog *findDialog;
    QAction *recentFilesActions[MAX_RECENT_FILES];
    QList<RecentFile> recentFiles;
    QList<QAction*> recentActions;
    QAction *undoAction;
    QAction *redoAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *delAction;
    QMenu * caseMenu;
    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
