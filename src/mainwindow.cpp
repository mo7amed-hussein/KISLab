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
#include "mainwindow.h"
#include<QDockWidget>
#include<QStatusBar>
#include<QMenu>
#include<QMenuBar>
#include<QToolBar>
#include<QIcon>
#include<QFileDialog>
#include<QFile>
#include<QDir>
#include<QApplication>
#include<QDebug>
#include<QInputDialog>
#include<QClipboard>
#include<QFileInfo>
#include<QMimeData>
#include<QDragEnterEvent>
#include<QSettings>
#include"settingdialog.h"
#include<QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
    readSetting();
    createStatusBar();
    createActions();
    checkClipboard();
    newFile();

    this->resize(800,600);
    this->setAcceptDrops(true);
    this->setAutoFillBackground(true);

    lastActivated.start();
    autosaveTimer.setSingleShot(false);
    updateSetting();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    fileMenu=menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar=addToolBar(tr("File"));
    fileToolBar->setContextMenuPolicy(Qt::PreventContextMenu);

    const QIcon newIcon=QIcon::fromTheme("document-new",QIcon(":/images/icons/new.png"));
    QAction *newAction=new QAction(newIcon,tr("&New"),this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setToolTip(tr("create a new file"));
    connect(newAction,&QAction::triggered,this,&MainWindow::newFile);
    fileMenu->addAction(newAction);
    fileToolBar->addAction(newAction);

    const QIcon openIcon=QIcon::fromTheme("document-open",QIcon(":/images/icons/open.png"));
    QAction *openAction=new QAction(openIcon,tr("&Open"),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setToolTip(tr("open a file"));
    connect(openAction,&QAction::triggered,this,&MainWindow::openfile);
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);

    const QIcon saveIcon=QIcon::fromTheme("document-save",QIcon(":/images/icons/save.png"));
    QAction *saveAction=new QAction(saveIcon,tr("&Save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setToolTip(tr("save a file"));
    connect(saveAction,&QAction::triggered,this,&MainWindow::save);
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    const QIcon saveAsIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
    QAction *saveAsAction=new QAction(saveAsIcon,tr("&SaveAs"),this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setToolTip(tr("save a file as"));
    connect(saveAsAction,&QAction::triggered,this,&MainWindow::saveAs);
    fileMenu->addAction(saveAsAction);
    fileToolBar->addAction(saveAsAction);

    const QIcon saveCopyIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
    QAction *saveCopyAction=new QAction(saveCopyIcon,tr("&Save a Copy As"),this);
    saveCopyAction->setShortcut(QKeySequence::SaveAs);
    saveCopyAction->setToolTip(tr("save a copy as"));
    connect(saveCopyAction,&QAction::triggered,this,&MainWindow::saveCopy);
    fileMenu->addAction(saveCopyAction);
   // fileToolBar->addAction(saveCopyAction);

    const QIcon saveAllIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
    QAction *saveAllAction=new QAction(saveAllIcon,tr("Save All"),this);
   // saveAllAction->setShortcut(QKeySequence::SaveAs);
    saveAllAction->setToolTip(tr("save all"));
    connect(saveAllAction,&QAction::triggered,this,&MainWindow::saveAll);
    fileMenu->addAction(saveAllAction);
   // fileToolBar->addAction(saveAllAction);

    fileToolBar->addSeparator();

    const QIcon closeIcon=QIcon::fromTheme("document-close",QIcon(":/images/icons/save.png"));
    QAction *closeAction=new QAction(closeIcon,tr("Close"),this);
    closeAction->setShortcut(QKeySequence::SaveAs);
    closeAction->setToolTip(tr("close a file"));
    connect(closeAction,&QAction::triggered,this,&MainWindow::closeFile);
    fileMenu->addAction(closeAction);
    //fileToolBar->addAction(closeAction);

    const QIcon closeAllIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
    QAction *closeAllAction=new QAction(closeAllIcon,tr("Close All"),this);
    closeAllAction->setShortcut(QKeySequence::SaveAs);
    closeAllAction->setToolTip(tr("close all files"));
    connect(closeAllAction,&QAction::triggered,this,&MainWindow::closeAll);
    fileMenu->addAction(closeAllAction);
    //fileToolBar->addAction(closeAction);

    fileMenu->addSeparator();
    //recent files
    createRecentfilesActions();
   // fileMenu->addSeparator();

    const QIcon quitIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
    quitAction=new QAction(quitIcon,tr("Quit"),this);
    quitAction->setShortcut(QKeySequence::SaveAs);
    quitAction->setToolTip(tr("Quit KISLab"));
    connect(quitAction,&QAction::triggered,this,&MainWindow::quitApp);
    fileMenu->addAction(quitAction);
    //fileToolBar->addAction(closeAction)

    QMenu *editMenu=menuBar()->addMenu(tr("&Edit"));
    fileToolBar->addSeparator();

    const QIcon undoIcon=QIcon::fromTheme("edit-undo",QIcon(":/images/icons/undo.png"));
    undoAction=new QAction(undoIcon,tr("Undo"),this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setToolTip(tr("undo"));
    undoAction->setEnabled(false);
    connect(undoAction,&QAction::triggered,this,&MainWindow::undo);
    editMenu->addAction(undoAction);
    fileToolBar->addAction(undoAction);

    const QIcon redoIcon=QIcon::fromTheme("edit-redo",QIcon(":/images/icons/redo.png"));
    redoAction=new QAction(redoIcon,tr("Redo"),this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setToolTip(tr("redo"));
    redoAction->setEnabled(false);
    connect(redoAction,&QAction::triggered,this,&MainWindow::redo);
    editMenu->addAction(redoAction);
    fileToolBar->addAction(redoAction);

    editMenu->addSeparator();
    fileToolBar->addSeparator();

    const QIcon cutIcon=QIcon::fromTheme("edit-cut",QIcon(":/images/icons/cut.png"));
    cutAction=new QAction(cutIcon,tr("cut"),this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setToolTip(tr("cut"));
    cutAction->setEnabled(false);
    connect(cutAction,&QAction::triggered,this,&MainWindow::cut);
    editMenu->addAction(cutAction);
    fileToolBar->addAction(cutAction);

    const QIcon copyIcon=QIcon::fromTheme("edit-copy",QIcon(":/images/icons/copy.png"));
    copyAction=new QAction(copyIcon,tr("Copy"),this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setToolTip(tr("copy"));
    copyAction->setEnabled(false);
    connect(copyAction,&QAction::triggered,this,&MainWindow::copy);
    editMenu->addAction(copyAction);
    fileToolBar->addAction(copyAction);

    const QIcon pasteIcon=QIcon::fromTheme("document-paste",QIcon(":/images/icons/paste.png"));
    pasteAction=new QAction(pasteIcon,tr("paste"),this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setToolTip(tr("paste"));
    pasteAction->setEnabled(false);
    connect(pasteAction,&QAction::triggered,this,&MainWindow::paste);
    editMenu->addAction(pasteAction);
    fileToolBar->addAction(pasteAction);
    fileToolBar->addSeparator();

    const QIcon delIcon=QIcon::fromTheme("edit-delete",QIcon(":/images/icons/del.png"));
    delAction=new QAction(delIcon,tr("Delete"),this);
    delAction->setShortcut(QKeySequence::Delete);
    delAction->setToolTip(tr("delete"));
    delAction->setEnabled(false);
    connect(delAction,&QAction::triggered,this,&MainWindow::del);
    editMenu->addAction(delAction);
    //fileToolBar->addAction(delAction);

    const QIcon selectIcon=QIcon::fromTheme("edit-selectall",QIcon(":/images/icons/select.png"));
    selectAction=new QAction(selectIcon,tr("Select All"),this);
    selectAction->setShortcut(QKeySequence::SelectAll);
    selectAction->setToolTip(tr("select all"));
    connect(selectAction,&QAction::triggered,this,&MainWindow::selectall);
    editMenu->addAction(selectAction);
    //fileToolBar->addAction(selectAction);

    editMenu->addSeparator();

    const QIcon clipboardIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    clipMenu=editMenu->addMenu(clipboardIcon,"copy To ClipBoard");

    const QIcon filePathIcon=QIcon::fromTheme("document-filePath",QIcon(":/images/icons/filePath.png"));
    QAction *filePathAction=new QAction(filePathIcon,tr("Current Full File Path"),this);
   // filePathAction->setShortcut(QKeySequence::);
    filePathAction->setToolTip(tr("Current Full File Path"));
    connect(filePathAction,&QAction::triggered,this,&MainWindow::copyFullPath);
    clipMenu->addAction(filePathAction);
    //fileToolBar->addAction(filePathAction);

    const QIcon fileNameIcon=QIcon::fromTheme("document-fileName",QIcon(":/images/icons/fileName.png"));
    QAction *fileNameAction=new QAction(fileNameIcon,tr("Current Filename"),this);
   // fileNameAction->setShortcut(QKeySequence::);
    fileNameAction->setToolTip(tr("Current Filename"));
    connect(fileNameAction,&QAction::triggered,this,&MainWindow::copyFileName);
    clipMenu->addAction(fileNameAction);
    //fileToolBar->addAction(fileNameAction);

    const QIcon fileDirIcon=QIcon::fromTheme("document-fileDir",QIcon(":/images/icons/fileDir.png"));
    QAction *fileDirAction=new QAction(fileDirIcon,tr("Current Directory Path"),this);
   // fileDirAction->setShortcut(QKeySequence::);
    fileDirAction->setToolTip(tr("current directory path"));
    connect(fileDirAction,&QAction::triggered,this,&MainWindow::copyDir);
    clipMenu->addAction(fileDirAction);
    //fileToolBar->addAction(fileDirAction);

    const QIcon caseIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    caseMenu=editMenu->addMenu(clipboardIcon,"Convert Case To");
    caseMenu->setEnabled(false);
    const QIcon upperCaseIcon=QIcon::fromTheme("document-upperCase",QIcon(":/images/icons/upperCase.png"));
    QAction *upperCaseAction=new QAction(upperCaseIcon,tr("UPPERCASE"),this);
   // upperCaseAction->setShortcut(QKeySequence::);
    upperCaseAction->setToolTip(tr("UPPERCASE"));
    connect(upperCaseAction,&QAction::triggered,this,&MainWindow::toUpperSlot);
    caseMenu->addAction(upperCaseAction);
    //fileToolBar->addAction(upperCaseAction);

    const QIcon lowCaseIcon=QIcon::fromTheme("document-lowCase",QIcon(":/images/icons/lowCase.png"));
    QAction *lowCaseAction=new QAction(lowCaseIcon,tr("lowcase"),this);
   // lowCaseAction->setShortcut(QKeySequence::);
    lowCaseAction->setToolTip(tr("lowcase"));
    connect(lowCaseAction,&QAction::triggered,this,&MainWindow::toLowerSlot);
    caseMenu->addAction(lowCaseAction);
    //fileToolBar->addAction(lowCaseAction);

    const QIcon timeIcon=QIcon::fromTheme("document-time",QIcon(":/images/icons/time.png"));
    timeAction=new QAction(timeIcon,tr("Time/Date"),this);
   // timeAction->setShortcut(QKeySequence::);
    timeAction->setToolTip(tr("Time/Date"));
    connect(timeAction,&QAction::triggered,this,&MainWindow::timeStampSlot);
    editMenu->addAction(timeAction);
    //fileToolBar->addAction(timeAction);

    editMenu->addSeparator();

    const QIcon prefIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    QAction *prefAction=new QAction(prefIcon,tr("Preferences"),this);
    prefAction->setShortcut(QKeySequence::Preferences);
    prefAction->setToolTip(tr("preferences"));
    connect(prefAction,&QAction::triggered,this,&MainWindow::openSetting);
    editMenu->addAction(prefAction);
    //fileToolBar->addAction(prefAction);

    QMenu *viewMenu=menuBar()->addMenu(tr("View"));

    viewMenu->addAction(browserDock->toggleViewAction());
    viewMenu->addAction(terminalDock->toggleViewAction());

    QAction *statusBarAction=new QAction(tr("StatusBar"),this);
    statusBarAction->setCheckable(true);
    connect(statusBarAction,&QAction::triggered,this,&MainWindow::toggleStatusbar);
    statusBarAction->setChecked(true);
    viewMenu->addAction(statusBarAction);
    //viewMenu->addAction(statusBar()->);

    searchMenu=menuBar()->addMenu(tr("Search"));

    const QIcon findIcon=QIcon::fromTheme("edit-find",QIcon(":/images/icons/find.png"));
    findAction=new QAction(findIcon,tr("Find"),this);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setToolTip(tr("find"));
    connect(findAction,&QAction::triggered,this,&MainWindow::find);
    searchMenu->addAction(findAction);
    fileToolBar->addAction(findAction);

    const QIcon goLineIcon=QIcon::fromTheme("document-goLine",QIcon(":/images/icons/goLine.png"));
    goLineAction=new QAction(goLineIcon,tr("GoTo Line"),this);
    connect(goLineAction,&QAction::triggered,this,&MainWindow::goLineSlot);
    searchMenu->addAction(goLineAction);
    //fileToolBar->addAction(goLineAction);

    QMenu *toolMenu=menuBar()->addMenu(tr("Tools"));
    const QIcon fileStatIcon=QIcon::fromTheme("document-fileStat",QIcon(":/images/icons/fileStat.png"));
    fileStatAction=new QAction(fileStatIcon,tr("File Statistics"),this);
    connect(fileStatAction,&QAction::triggered,this,&MainWindow::fileStatSlot);
    toolMenu->addAction(fileStatAction);
    //fileToolBar->addAction(fileStatAction);

    QMenu *helpMenu=menuBar()->addMenu(tr("Help"));

    const QIcon aboutIcon=QIcon::fromTheme("document-about",QIcon(":/images/icons/about.png"));
    QAction *aboutAction=new QAction(aboutIcon,tr("about"),this);
    connect(aboutAction,&QAction::triggered,this,&MainWindow::about);
    helpMenu->addAction(aboutAction);
    //fileToolBar->addAction(aboutAction);

    const QIcon aboutQtIcon=QIcon::fromTheme("document-aboutQt",QIcon(":/images/icons/aboutQt.png"));
    QAction *aboutQtAction=new QAction(aboutQtIcon,tr("aboutQt"),this);
   // aboutQtAction->setShortcut(QKeySequence::aboutQt);
    aboutQtAction->setToolTip(tr("aboutQt"));
    connect(aboutQtAction,&QAction::triggered,qApp,&QApplication::aboutQt);
    helpMenu->addAction(aboutQtAction);
    //fileToolBar->addAction(aboutQtAction);

}


void MainWindow::createWidgets()
{
    editor=new Editor(this);
    setCentralWidget(editor);

    browserDock=new QDockWidget(tr("Files"));
    browser =new Browser(browserDock);
    browserDock->setFeatures(QDockWidget::NoDockWidgetFeatures|QDockWidget::DockWidgetClosable);
    browserDock->setWidget(browser);
    browserDock->setContextMenuPolicy(Qt::PreventContextMenu);

    addDockWidget(Qt::RightDockWidgetArea,browserDock);

    terminalDock=new QDockWidget(tr("Terminal"));
    terminalDock->setFeatures(QDockWidget::DockWidgetClosable);
    terminal=new Terminal(terminalDock);
    terminalDock->setWidget(terminal);
    terminalDock->setAcceptDrops(false);
    terminalDock->setContextMenuPolicy(Qt::PreventContextMenu);

    addDockWidget(Qt::BottomDockWidgetArea,terminalDock);

    connect(terminal,&Terminal::closeTerminaldock,terminalDock,&QDockWidget::hide);
    connect(terminalDock,&QDockWidget::visibilityChanged,terminal,&Terminal::toggleShow);
    connect(editor,SIGNAL(cursorChanged(int,int)),this,SLOT(updateStatusBar(int,int)));
    connect(editor,&Editor::fileIsNew,this,&MainWindow::saveAs);
    connect(browser,&Browser::showFile,editor,&Editor::showDoc);
    connect(browser,&Browser::closeFile,editor,&Editor::closeFile);
    connect(editor,&Editor::copyChangedSig,this,&MainWindow::checkCopy);
    connect(editor,&Editor::fileChangedSig,this,&MainWindow::fileChangedSlot);
    connect(editor,&Editor::filenameChanged,browser,&Browser::changeFilename);
    connect(editor,&Editor::removeFile,browser,&Browser::removeChild);
    connect(editor,&Editor::noFilesChanged,this,&MainWindow::noFilesChanged);
    connect(&autosaveTimer,&QTimer::timeout,this,&MainWindow::autosavefiles);
}

void MainWindow::createStatusBar()
{

    lineLabel=new QLabel();
    lineLabel->setText("Ln: 9999 ,col: 9999");

    lineLabel->setAlignment(Qt::AlignHCenter);
    lineLabel->setFrameStyle(QFrame::NoFrame);
    statusBar()->addPermanentWidget(lineLabel,0);
    statusBar()->showMessage("Keep It Simple");
    statusBar()->adjustSize();

}

void MainWindow::newFile()
{
    QString name=editor->newFile();
    browser->addfile(name,"");
}

void MainWindow::openfile()
{
    QStringList filePaths=QFileDialog::getOpenFileNames(this,tr("Select one or more files to open"),QDir::currentPath(),
         "All files (*.*);;"
         "Normal text file (*.txt *.ini);;"
         "Batch file (*.bat *.cmd *.nt);;"
         "C/C++ source file (*.c *.cpp *.cc *.cxx *.h *.hpp *.hxx);;"
         "C# source file (*.cs);;"
         "CMake file (*.cmake);;"
         "CoffeeScript file(*.litcoffee);;"
         "CSS file (*.css );;"
         "D file (*.d);;"
         "Diff file(*.diff *.patch);;"
         "Fortran free form (*.f *.for *.f90 *.f95 *.f2k);;"
         "Fortran fixed form (*.f77);;"
         "HTML file (*.htm *.html *.shtm *.shtml *.xhtml *.hta);;"
         "Java source file (*.java);;"
         "Java script file (*.js);;"
         "Lua script file (*.lua);;"
         "Makefile (*.mak);;"
         "Matlab file(*.m);;"
         "Pascal file (*.pas *.inc);;"
         "Perl file (*pl *.pm *.plx);;"
         "Postscript file (*.ps);;"
         "Properties file (*.properties);;"
         "Python file (*.py *.pyw);;"
         "Ruby file (*.rb *.rbw);;"
         "SQL file(*.sql);;"
         "TCL file (*.tcl);;"
         "TeX file (*.tex);;"
         "VHDL file (*.vhd *.vhdl);;"
         "Verilog file (*.v *.sv *.vh *.svh);;"
         "XML file (*.xml *.xsml *.xsl *.kml *.wsdl *.xlf *xliff);;"
         "YAML file (*.yml)");

    foreach (QString file,filePaths)
    {

        if(file.isEmpty())
            return;

        QFileInfo f(file);
        if(!browser->checkOpenedFile(f.fileName(),file))
        {
        editor->openFile(file);

        browser->addfile(f.fileName(),file);

        addRecentFile(file);
        createRecentfilesActions();
        }


    }




}

void MainWindow::save()
{
 editor->save();
}

void MainWindow::undo()
{
    editor->undo();
    undoAction->setEnabled(editor->isUndoAvailable());
}

void MainWindow::redo()
{
    editor->redo();
    redoAction->setEnabled(editor->isRedoAvailable());
}

void MainWindow::copy()
{
    editor->copy();
}

void MainWindow::cut()
{
    editor->cut();
}

void MainWindow::paste()
{
    editor->paste();
}

void MainWindow::del()
{
    editor->del();
}

void MainWindow::selectall()
{
    editor->selectAll();
}

void MainWindow::saveAs()
{
    QString filename=QFileDialog::getSaveFileName(this,tr("save as"));
    if(filename.isEmpty())
        return;
    editor->saveAs(filename);

}

void MainWindow::saveAll()
{
editor->saveAll();
}

void MainWindow::saveCopy()
{
    QString filename=QFileDialog::getSaveFileName(this,tr("save as"));
    if(filename.isEmpty())
        return;
    editor->saveCopy(filename);

}
void MainWindow::closeFile()
{
    editor->close();
}

void MainWindow::updateStatusBar(int l,int c)
{
    QString line=tr("Ln: %1 , col: %2      ").arg(l).arg(c);

    lineLabel->setText(line);
}

void MainWindow::closeAll()
{
    editor->closeAll();
}

void MainWindow::find()
{
 editor->showFindWidget();
}

void MainWindow::toggleStatusbar()
{
    if(statusBar()->isHidden())
    {
        statusBar()->setVisible(true);
    }
    else
    {
        statusBar()->setVisible(false);
    }
}

 void MainWindow::quitApp()
 {
     if(editor->closeAll())
     {
        saveSetting();
        qApp->quit();
     }
 }

 bool MainWindow::event(QEvent * event)
 {

     switch (event->type()) {
     case QEvent::WindowActivate:
          //  qDebug()<<"elapsed "<<lastActivated.elapsed();
            if(lastActivated.elapsed()>30000)
            {
                //qDebug()<<"check for change";
                editor->checkExternalChange();

            }

             break;
     case QEvent::WindowDeactivate:
                 lastActivated.restart();
                 //qDebug()<<"deactivated";
                 break;
     case QEvent::Clipboard:
         //qDebug()<<"clipboard";
             checkClipboard();
         break;
     default:
         break;
     }
     return QMainWindow::event(event);

 }

 void MainWindow::goLineSlot()
 {
    editor->goLine();
 }
 void MainWindow::toLowerSlot()
 {
     editor->toLowerCase();
 }

 void MainWindow::toUpperSlot()
 {
     editor->toUpperCase();
 }
 void MainWindow::timeStampSlot()
 {
   editor->timeStamp();
 }
 void MainWindow::copyFileName()
 {
     QFileInfo f(editor->getCurrentFilePath());
     QClipboard *clip=QApplication::clipboard();
     clip->setText(f.fileName());

 }

 void MainWindow::copyFullPath()
 {

     QClipboard *clip=QApplication::clipboard();
     clip->setText(editor->getCurrentFilePath());
 }

 void MainWindow::copyDir()
 {
     QFileInfo f(editor->getCurrentFilePath());
     QClipboard *clip=QApplication::clipboard();
     clip->setText(f.path());

 }
 void MainWindow::fileStatSlot()
 {
     editor->fileStatDiag();
 }

 void MainWindow::checkClipboard()
 {
     const QClipboard *clipboard = QApplication::clipboard();
     const QMimeData *mimeData = clipboard->mimeData();
     if(mimeData->hasHtml()|mimeData->hasText()|mimeData->hasUrls())
     {
         pasteAction->setEnabled(true);
     }
     else
     {
       pasteAction->setEnabled(false);
     }

 }

 void MainWindow::checkCopy(bool b)
 {
     copyAction->setEnabled(b);
     cutAction->setEnabled(b);
     delAction->setEnabled(b);
     caseMenu->setEnabled(b);
 }
 void MainWindow::fileChangedSlot(bool s)
 {

         undoAction->setEnabled(s);
         redoAction->setEnabled(s);
 }
 void MainWindow::dragEnterEvent(QDragEnterEvent *event)
 {


     if (event->mimeData()->hasFormat(QLatin1String("text/uri-list")))
         {
             event->acceptProposedAction();
            // this->setBackgroundRole(QPalette::Highlight);
         }

 }

 void MainWindow::dropEvent(QDropEvent *event)
 {
     QList<QUrl> urlList;
     QString fileName;
     QFileInfo info;

     foreach (QString format, event->mimeData()->formats())
     {

         if(format==QLatin1String("text/uri-list"))
         {
             urlList =event->mimeData()->urls();
            for(int i=0;i<urlList.size();i++)
            {
                fileName=urlList[i].toLocalFile();
                info.setFile(fileName);
                if(info.isFile())
                {
                    qDebug()<<fileName;
                    editor->openFile(fileName);
                    browser->addfile(fileName,"");
                }
            }

         }

     }
  //   setBackgroundRole(QPalette::NoRole);

 }

 void MainWindow::about()
 {

     menuBar()->setEnabled(false);
     AboutDialog *aboutDiag=new AboutDialog(this);

     aboutDiag->exec();
     menuBar()->setEnabled(true);
 }

 void MainWindow::closeEvent(QCloseEvent * event)
 {
     quitApp();
     event->ignore();
 }

 void MainWindow::readSetting()
 {
     QSettings setting;
    int size=setting.beginReadArray("recentFiles");
    for(int i=0;i<size && i<MAX_RECENT_FILES;i++)
    {
        RecentFile f;
        setting.setArrayIndex(i);
        f.filePath=setting.value("filePath","").toString();
        recentFiles.append(f);
    }
     setting.endArray();
     bool maxFlag=setting.value("WINDOWSTATE",false).toBool();
    if(maxFlag)
    {
        this->showMaximized();
    }
     browserDock->setHidden(setting.value("BROWSERSTATE",true).toBool());
     terminalDock->setHidden(setting.value("TERMINALSTATE",true).toBool());

    // qDebug()<<"list sizes "<<list.size();

 }

 void MainWindow::openRecent()
 {
     QAction *action=qobject_cast<QAction *>(sender());
     if(action)
       {
     qDebug()<<action->data().toString();

     QFileInfo f(action->data().toString());
     if(!browser->checkOpenedFile(f.fileName(),action->data().toString()))
     {
      editor->openFile(action->data().toString());
   //  editor->openFile(filename);

     browser->addfile(f.fileName(),action->data().toString());


     }

     }



 }
 void MainWindow::createRecentfilesActions()
 {
     //recentActions.clear();
     int size=recentFiles.size();
     int recentAc=recentActions.size();
   //  qDebug()<<"sizes "<<recentFiles.size();
     for(int i=0;i<recentAc;i++)
     {
         fileMenu->removeAction(recentActions[i]);
         delete recentActions[i];

     }
     recentActions.clear();
     for(int i=0;i<size && i<MAX_RECENT_FILES;i++)
     {
         QFileInfo f(recentFiles[i].filePath);

        QAction *tmp=new QAction(tr("%1 . %2").arg(i+1).arg(f.fileName()),this);

         tmp->setData(recentFiles[i].filePath);
         connect(tmp,&QAction::triggered,this,&MainWindow::openRecent);
         recentActions.append(tmp);
         //fileMenu->addAction(recentFilesActions[i]);

     }
     if(size>0)
     {
         fileMenu->insertActions(quitAction,recentActions);
         fileMenu->insertSeparator(quitAction);

     }
 }
void MainWindow::addRecentFile(QString &file)
 {
     RecentFile f;
     f.filePath=file;
     recentFiles.push_front(f);
     if(recentFiles.size()>MAX_RECENT_FILES)
     {
         recentFiles.pop_back();
     }

 }

void MainWindow::openSetting()
 {
    menuBar()->setEnabled(false);
     SettingDialog s(this);
     if(s.exec()==1)
     {
         editor->updateSetting();
         this->updateSetting();
     }
     menuBar()->setEnabled(true);
 }

void MainWindow::saveSetting()
 {
     QSettings setting;
    int size=recentFiles.size();
    setting.beginWriteArray("recentFiles");
    for(int i=0;i<size && i<MAX_RECENT_FILES;i++)
    {

        setting.setArrayIndex(i);
        setting.setValue("filePath",recentFiles[i].filePath);

    }
    setting.endArray();
    setting.setValue("WINDOWSTATE",this->isMaximized());
    setting.setValue("BROWSERSTATE",browserDock->isHidden());
    setting.setValue("TERMINALSTATE",terminalDock->isHidden());

 }

void MainWindow::noFilesChanged(bool b)
 {
     if(b)
     {
         pasteAction->setEnabled(false);
         fileStatAction->setEnabled(false);
        findAction->setEnabled(false);
        goLineAction->setEnabled(false);
         timeAction->setEnabled(false);
         clipMenu->setEnabled(false);
         selectAction->setEnabled(false);

     }
     else
     {
         checkClipboard();
         fileStatAction->setEnabled(true);
         findAction->setEnabled(true);
         goLineAction->setEnabled(true);
          timeAction->setEnabled(true);
          clipMenu->setEnabled(true);
          selectAction->setEnabled(true);

     }
 }

 void MainWindow::autosavefiles()
  {
      editor->autoSaveAll();
      qDebug()<<"timeout";

  }
 void MainWindow::updateSetting()
   {
    QSettings set;
    bool saveFlag=set.value("AUTOSAVE",false).toBool();
    int saveTime=set.value("SAVE_TIME",5).toInt();
    autosaveTimer.setInterval(saveTime*60000);
    // qDebug()<<"setting here1";
    if(saveFlag)
    {
      //  qDebug()<<"setting here2";
        autosaveTimer.start();
    }
    else
    {
        autosaveTimer.stop();
    }

   }
