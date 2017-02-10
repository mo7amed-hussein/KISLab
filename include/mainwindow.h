/***************************************************************************
 *   Copyright (C) 2017 by Mohamed Hussein                                 *
 *   m.hussein1389@gmail.com                                               *
     https://github.com/mo7amed-hussein/                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "editor.h"
#include "terminal.h"
#include "browser.h"
#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include<QTimer>
#include<QEvent>
#include <findwidget.h>
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

    void addRecentFile(QString &file);
    void updateSetting();


 public slots:
    void autosavefiles();
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

    void openSetting();
     void noFilesChanged(bool b);

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


    QList<RecentFile> recentFiles;
    QList<QAction*> recentActions;
    QAction *undoAction;
    QAction *redoAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *fileStatAction;
    QMenu *searchMenu;
    QAction *timeAction;
    QMenu *clipMenu;
    QAction *selectAction;
    QAction *findAction;
    QAction *goLineAction;
    QAction *delAction;
    QMenu * caseMenu;
    QMenu *fileMenu;
    QAction *quitAction;
    QTime lastActivated;
    QTimer autosaveTimer;
};

#endif // MAINWINDOW_H
