#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTabWidget>
//#include <Qsci/qsciscintilla.h>
#include <QList>
#include "finddialog.h"
#include "texteditor.h"
class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);


    void openFile(QString filetxt);
    void newFile();
    void undo();
    void redo();
    void copy();
    void paste();
    void cut();
    void del();
    void selectAll();
    void save();
    void save(QString name);
    void saveAs(QString name);
    void saveCopy(QString name);
    void saveAll();


    bool close();
    bool closeFile(QString file);
    bool closeAll();

    void goLine();
    void toLowerCase();
    void toUpperCase();
    void timeStamp();
    void showFindDialog();
    QString getCurrentFilePath();
    bool isUndoAvailable();
    bool isRedoAvailable();
    void fileStatDiag();
  //  QsciScintilla *currentEditor;
signals:

    void cursorChanged(int l,int c);
    void fileIsNew();
    void copyChangedSig(bool c);
    void fileChangedSig(bool s);
public slots:
    void tabChange(int i);
    bool tabClose(int i);
    void closeTabContext(bool b);
    void closeAllTabContext(bool b);
    void saveTabContext(bool b);
    void editorCursorChanged(int l,int c);
    void closeFindDialog();
    void findNxtSlot(const QString &expr,bool re,bool cs,bool wo,bool wrap);
    void showDoc(QString filePath);
     void onCustomContextMenuRequested(const QPoint& pos);
     void copyChangedSlot(bool c);
     void fileChangedSlot(bool s);
     void replace(const QString &replaceStr);
private:
 TextEditor *currentEditor;
 QString currentFile;

 QTabWidget *editorTabs;
 QList<QString*>filesList;
 FindDialog *find;
 //QWidget *goLineWidget;
 int newCount;
int clickedTab;
};

#endif // EDITOR_H
