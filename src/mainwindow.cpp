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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
    createStatusBar();
    createActions();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    QMenu *fileMenu=menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar=addToolBar(tr("File"));

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
    connect(saveAllAction,&QAction::triggered,this,&MainWindow::save);
    fileMenu->addAction(saveAllAction);
   // fileToolBar->addAction(saveAllAction);

    fileToolBar->addSeparator();

    const QIcon closeIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
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
    connect(closeAllAction,&QAction::triggered,this,&MainWindow::save);
    fileMenu->addAction(closeAllAction);
    //fileToolBar->addAction(closeAction);

    fileMenu->addSeparator();
    //recent files
    fileMenu->addSeparator();

    const QIcon quitIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
    QAction *quitAction=new QAction(quitIcon,tr("Quit"),this);
    quitAction->setShortcut(QKeySequence::SaveAs);
    quitAction->setToolTip(tr("Quit KISLab"));
    connect(quitAction,&QAction::triggered,this,&MainWindow::save);
    fileMenu->addAction(quitAction);
    //fileToolBar->addAction(closeAction)

    QMenu *editMenu=menuBar()->addMenu(tr("&Edit"));
    fileToolBar->addSeparator();

    const QIcon undoIcon=QIcon::fromTheme("document-undo",QIcon(":/images/icons/undo.png"));
    QAction *undoAction=new QAction(undoIcon,tr("Undo"),this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setToolTip(tr("undo"));
    connect(undoAction,&QAction::triggered,this,&MainWindow::undo);
    editMenu->addAction(undoAction);
    fileToolBar->addAction(undoAction);

    const QIcon redoIcon=QIcon::fromTheme("document-redo",QIcon(":/images/icons/redo.png"));
    QAction *redoAction=new QAction(redoIcon,tr("Redo"),this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setToolTip(tr("redo"));
    connect(redoAction,&QAction::triggered,this,&MainWindow::redo);
    editMenu->addAction(redoAction);
    fileToolBar->addAction(redoAction);

    editMenu->addSeparator();
    fileToolBar->addSeparator();

    const QIcon cutIcon=QIcon::fromTheme("document-cut",QIcon(":/images/icons/cut.png"));
    QAction *cutAction=new QAction(cutIcon,tr("cut"),this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setToolTip(tr("cut"));
    connect(cutAction,&QAction::triggered,this,&MainWindow::cut);
    editMenu->addAction(cutAction);
    fileToolBar->addAction(cutAction);

    const QIcon copyIcon=QIcon::fromTheme("document-copy",QIcon(":/images/icons/copy.png"));
    QAction *copyAction=new QAction(copyIcon,tr("Copy"),this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setToolTip(tr("copy"));
    connect(copyAction,&QAction::triggered,this,&MainWindow::copy);
    editMenu->addAction(copyAction);
    fileToolBar->addAction(copyAction);

    const QIcon pasteIcon=QIcon::fromTheme("document-paste",QIcon(":/images/icons/paste.png"));
    QAction *pasteAction=new QAction(pasteIcon,tr("paste"),this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setToolTip(tr("paste"));
    connect(pasteAction,&QAction::triggered,this,&MainWindow::paste);
    editMenu->addAction(pasteAction);
    fileToolBar->addAction(pasteAction);
    fileToolBar->addSeparator();

    const QIcon delIcon=QIcon::fromTheme("document-delete",QIcon(":/images/icons/del.png"));
    QAction *delAction=new QAction(delIcon,tr("Delete"),this);
    delAction->setShortcut(QKeySequence::Delete);
    delAction->setToolTip(tr("delete"));
    connect(delAction,&QAction::triggered,this,&MainWindow::del);
    editMenu->addAction(delAction);
    //fileToolBar->addAction(delAction);

    const QIcon selectIcon=QIcon::fromTheme("document-select",QIcon(":/images/icons/select.png"));
    QAction *selectAction=new QAction(selectIcon,tr("Select All"),this);
    selectAction->setShortcut(QKeySequence::SelectAll);
    selectAction->setToolTip(tr("select all"));
    connect(selectAction,&QAction::triggered,this,&MainWindow::selectall);
    editMenu->addAction(selectAction);
    //fileToolBar->addAction(selectAction);

    editMenu->addSeparator();

    const QIcon clipboardIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    QMenu *clipMenu=editMenu->addMenu(clipboardIcon,"copy To ClipBoard");

    const QIcon filePathIcon=QIcon::fromTheme("document-filePath",QIcon(":/images/icons/filePath.png"));
    QAction *filePathAction=new QAction(filePathIcon,tr("Current Full File Path"),this);
   // filePathAction->setShortcut(QKeySequence::);
    filePathAction->setToolTip(tr("Current Full File Path"));
    connect(filePathAction,&QAction::triggered,this,&MainWindow::save);
    clipMenu->addAction(filePathAction);
    //fileToolBar->addAction(filePathAction);

    const QIcon fileNameIcon=QIcon::fromTheme("document-fileName",QIcon(":/images/icons/fileName.png"));
    QAction *fileNameAction=new QAction(fileNameIcon,tr("Current Filename"),this);
   // fileNameAction->setShortcut(QKeySequence::);
    fileNameAction->setToolTip(tr("Current Filename"));
    connect(fileNameAction,&QAction::triggered,this,&MainWindow::save);
    clipMenu->addAction(fileNameAction);
    //fileToolBar->addAction(fileNameAction);

    const QIcon fileDirIcon=QIcon::fromTheme("document-fileDir",QIcon(":/images/icons/fileDir.png"));
    QAction *fileDirAction=new QAction(fileDirIcon,tr("Current Directory Path"),this);
   // fileDirAction->setShortcut(QKeySequence::);
    fileDirAction->setToolTip(tr("current directory path"));
    connect(fileDirAction,&QAction::triggered,this,&MainWindow::save);
    clipMenu->addAction(fileDirAction);
    //fileToolBar->addAction(fileDirAction);

    const QIcon caseIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    QMenu *caseMenu=editMenu->addMenu(clipboardIcon,"Convert Case To");

    const QIcon upperCaseIcon=QIcon::fromTheme("document-upperCase",QIcon(":/images/icons/upperCase.png"));
    QAction *upperCaseAction=new QAction(upperCaseIcon,tr("UPPERCASE"),this);
   // upperCaseAction->setShortcut(QKeySequence::);
    upperCaseAction->setToolTip(tr("UPPERCASE"));
    connect(upperCaseAction,&QAction::triggered,this,&MainWindow::save);
    caseMenu->addAction(upperCaseAction);
    //fileToolBar->addAction(upperCaseAction);

    const QIcon lowCaseIcon=QIcon::fromTheme("document-lowCase",QIcon(":/images/icons/lowCase.png"));
    QAction *lowCaseAction=new QAction(lowCaseIcon,tr("lowcase"),this);
   // lowCaseAction->setShortcut(QKeySequence::);
    lowCaseAction->setToolTip(tr("lowcase"));
    connect(lowCaseAction,&QAction::triggered,this,&MainWindow::save);
    caseMenu->addAction(lowCaseAction);
    //fileToolBar->addAction(lowCaseAction);

    const QIcon commentIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    QMenu *commentMenu=editMenu->addMenu(commentIcon,"Comment/UnComment");

    const QIcon lineCommentIcon=QIcon::fromTheme("document-lineComment",QIcon(":/images/icons/lineComment.png"));
    QAction *lineCommentAction=new QAction(lineCommentIcon,tr("Single Line Comment"),this);
   // lineCommentAction->setShortcut(QKeySequence::);
    lineCommentAction->setToolTip(tr("single line comment"));
    connect(lineCommentAction,&QAction::triggered,this,&MainWindow::save);
    commentMenu->addAction(lineCommentAction);
    //fileToolBar->addAction(lineCommentAction);

    const QIcon lineUnCommentIcon=QIcon::fromTheme("document-lineUnComment",QIcon(":/images/icons/lineUnComment.png"));
    QAction *lineUnCommentAction=new QAction(lineUnCommentIcon,tr("Single Line UnComment"),this);
   // lineUnCommentAction->setShortcut(QKeySequence::);
    lineUnCommentAction->setToolTip(tr("single line uncomment"));
    connect(lineUnCommentAction,&QAction::triggered,this,&MainWindow::save);
    commentMenu->addAction(lineUnCommentAction);
    //fileToolBar->addAction(lineUnCommentAction);

    const QIcon blockCommentIcon=QIcon::fromTheme("document-blockComment",QIcon(":/images/icons/blockComment.png"));
    QAction *blockCommentAction=new QAction(blockCommentIcon,tr("Block Comment"),this);
   // blockCommentAction->setShortcut(QKeySequence::);
    blockCommentAction->setToolTip(tr("block comment"));
    connect(blockCommentAction,&QAction::triggered,this,&MainWindow::save);
    commentMenu->addAction(blockCommentAction);
    //fileToolBar->addAction(blockCommentAction);

    const QIcon blockUnUnComIcon=QIcon::fromTheme("document-blockUnCom",QIcon(":/images/icons/blockUnCom.png"));
    QAction *blockUnComAction=new QAction(blockUnUnComIcon,tr("Block UnCom"),this);
   // blockUnComAction->setShortcut(QKeySequence::);
    blockUnComAction->setToolTip(tr("block UnCommment"));
    connect(blockUnComAction,&QAction::triggered,this,&MainWindow::save);
    commentMenu->addAction(blockUnComAction);
    //fileToolBar->addAction(blockUnComAction);

    const QIcon timeIcon=QIcon::fromTheme("document-time",QIcon(":/images/icons/time.png"));
    QAction *timeAction=new QAction(timeIcon,tr("Time/Date"),this);
   // timeAction->setShortcut(QKeySequence::);
    timeAction->setToolTip(tr("Time/Date"));
    connect(timeAction,&QAction::triggered,this,&MainWindow::save);
    editMenu->addAction(timeAction);
    //fileToolBar->addAction(timeAction);

    editMenu->addSeparator();

    const QIcon prefIcon=QIcon::fromTheme("document-pref",QIcon(":/images/icons/pref.png"));
    QAction *prefAction=new QAction(prefIcon,tr("Preferences"),this);
    prefAction->setShortcut(QKeySequence::Preferences);
    prefAction->setToolTip(tr("preferences"));
    connect(prefAction,&QAction::triggered,this,&MainWindow::save);
    editMenu->addAction(prefAction);
    //fileToolBar->addAction(prefAction);

    QMenu *viewMenu=menuBar()->addMenu(tr("View"));

    viewMenu->addAction(browserDock->toggleViewAction());
    viewMenu->addAction(terminalDock->toggleViewAction());
    QAction *statusBarAction=new QAction(tr("StatusBar"),this);
   // statusBarAction->setShortcut(QKeySequence::statusBarerences);
    statusBarAction->setToolTip(tr("statusBar"));
    statusBarAction->setCheckable(true);
    connect(statusBarAction,&QAction::triggered,this,&MainWindow::save);
    viewMenu->addAction(statusBarAction);
    //viewMenu->addAction(statusBar()->);

    QMenu *searchMenu=menuBar()->addMenu(tr("Search"));

    const QIcon findIcon=QIcon::fromTheme("document-find",QIcon(":/images/icons/find.png"));
    QAction *findAction=new QAction(findIcon,tr("Find"),this);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setToolTip(tr("find"));
    connect(findAction,&QAction::triggered,this,&MainWindow::save);
    searchMenu->addAction(findAction);
    fileToolBar->addAction(findAction);

    const QIcon findNxtIcon=QIcon::fromTheme("document-findNxt",QIcon(":/images/icons/findNxt.png"));
    QAction *findNxtAction=new QAction(findNxtIcon,tr("Find Next"),this);
    findNxtAction->setShortcut(QKeySequence::FindNext);
    findNxtAction->setToolTip(tr("find next"));
    connect(findNxtAction,&QAction::triggered,this,&MainWindow::save);
    searchMenu->addAction(findNxtAction);
    //fileToolBar->addAction(findNxtAction);

    const QIcon findPrevIcon=QIcon::fromTheme("document-findPrev",QIcon(":/images/icons/findPrev.png"));
    QAction *findPrevAction=new QAction(findPrevIcon,tr("Find Previous"),this);
    findPrevAction->setShortcut(QKeySequence::FindPrevious);
    findPrevAction->setToolTip(tr("find Previous"));
    connect(findPrevAction,&QAction::triggered,this,&MainWindow::save);
    searchMenu->addAction(findPrevAction);
    //fileToolBar->addAction(findPrevAction);

    const QIcon replaceIcon=QIcon::fromTheme("document-replace",QIcon(":/images/icons/replace.png"));
    QAction *replaceAction=new QAction(replaceIcon,tr("Replace"),this);
    replaceAction->setShortcut(QKeySequence::Replace);
    replaceAction->setToolTip(tr("Replace"));
    connect(replaceAction,&QAction::triggered,this,&MainWindow::save);
    searchMenu->addAction(replaceAction);
    fileToolBar->addAction(replaceAction);

    const QIcon goLineIcon=QIcon::fromTheme("document-goLine",QIcon(":/images/icons/goLine.png"));
    QAction *goLineAction=new QAction(goLineIcon,tr("GoTo Line"),this);
   // goLineAction->setShortcut(QKeySequence::goLine);
    goLineAction->setToolTip(tr("goto line"));
    connect(goLineAction,&QAction::triggered,this,&MainWindow::save);
    searchMenu->addAction(goLineAction);
    //fileToolBar->addAction(goLineAction);

    QMenu *toolMenu=menuBar()->addMenu(tr("Tools"));
    const QIcon fileStatIcon=QIcon::fromTheme("document-fileStat",QIcon(":/images/icons/fileStat.png"));
    QAction *fileStatAction=new QAction(fileStatIcon,tr("File Statistics"),this);
   // fileStatAction->setShortcut(QKeySequence::fileStat);
    fileStatAction->setToolTip(tr("File Statistics"));
    connect(fileStatAction,&QAction::triggered,this,&MainWindow::save);
    toolMenu->addAction(fileStatAction);
    //fileToolBar->addAction(fileStatAction);

    QMenu *helpMenu=menuBar()->addMenu(tr("Help"));

    const QIcon contentIcon=QIcon::fromTheme("document-content",QIcon(":/images/icons/content.png"));
    QAction *contentAction=new QAction(contentIcon,tr("Contents"),this);
   // contentAction->setShortcut(QKeySequence::content);
    contentAction->setToolTip(tr("contents"));
    connect(contentAction,&QAction::triggered,this,&MainWindow::save);
    helpMenu->addAction(contentAction);
    //fileToolBar->addAction(contentAction);

    const QIcon aboutIcon=QIcon::fromTheme("document-about",QIcon(":/images/icons/about.png"));
    QAction *aboutAction=new QAction(aboutIcon,tr("about"),this);
   // aboutAction->setShortcut(QKeySequence::about);
    aboutAction->setToolTip(tr("about"));
    connect(aboutAction,&QAction::triggered,this,&MainWindow::save);
    helpMenu->addAction(aboutAction);
    //fileToolBar->addAction(aboutAction);

    const QIcon aboutQtIcon=QIcon::fromTheme("document-aboutQt",QIcon(":/images/icons/aboutQt.png"));
    QAction *aboutQtAction=new QAction(aboutQtIcon,tr("aboutQt"),this);
   // aboutQtAction->setShortcut(QKeySequence::aboutQt);
    aboutQtAction->setToolTip(tr("aboutQt"));
    connect(aboutQtAction,&QAction::triggered,this,&MainWindow::save);
    helpMenu->addAction(aboutQtAction);
    //fileToolBar->addAction(aboutQtAction);







}

void MainWindow::createToolBar()
{

}

void MainWindow::createMenuBar()
{

}

void MainWindow::createWidgets()
{
    editor=new Editor(this);
    setCentralWidget(editor);


    terminal=new Terminal();

   // browser->show();

    browserDock=new QDockWidget(tr("Files Tree"));

    browser =new Browser(browserDock);

    browserDock->setWidget(browser);
    addDockWidget(Qt::RightDockWidgetArea,browserDock);

    terminalDock=new QDockWidget(tr("Terminal"));
    browserDock->setWidget(terminal);
    addDockWidget(Qt::BottomDockWidgetArea,terminalDock);

    connect(editor,&Editor::cursorChanged,this,&MainWindow::updateStatusBar);


}

void MainWindow::createStatusBar()
{

    lineLabel=new QLabel();
    lineLabel->setText("Line : 0");

    colLabel=new QLabel();
    colLabel->setText("col : 0");

    statusBar()->addPermanentWidget(lineLabel);
    statusBar()->addPermanentWidget(colLabel);
    statusBar()->showMessage("wellcome");

}

void MainWindow::newFile()
{
    editor->newFile();
}

void MainWindow::openfile()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("open file"),QDir::currentPath(),
         "(*.c *.cpp *.h *.asm *.xml)");

    if(filename.isEmpty())
        return;

    editor->openFile(filename);

}

void MainWindow::save()
{
 editor->save();
}

void MainWindow::undo()
{
    editor->undo();
}

void MainWindow::redo()
{
    editor->redo();
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
    QString line=tr("Line : %1").arg(l);
    QString col=tr("Col : %1").arg(c);
    lineLabel->setText(line);
    colLabel->setText(col);
}
