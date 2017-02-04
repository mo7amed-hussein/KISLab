#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTabWidget>
#include <Qsci/qsciscintilla.h>
class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);

    void initializeEditor();
    void initializeLexer();
    void initializeFolding();
    void initializeMargin();
    void initializeCaretLine();
    void initializeFont();
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


    void close();

  //  QsciScintilla *currentEditor;
signals:

    void cursorChanged(int l,int c);

public slots:
    void tabChange(int i);
    void tabClose(int i);
    void editorCursorChanged(int l,int c);

private:
 QsciScintilla *currentEditor;
 QString currentFile;

 QTabWidget *editorTabs;

};

#endif // EDITOR_H
