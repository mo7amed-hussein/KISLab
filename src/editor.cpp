#include "editor.h"
#include <Qsci/qscilexercpp.h>
#include <QGridLayout>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileInfo>
#include<QDebug>
Editor::Editor(QWidget *parent) : QWidget(parent)
{


    editorTabs=new QTabWidget(this);
    editorTabs->setTabsClosable(true);
    currentEditor=new QsciScintilla(this);

    initializeEditor();
    QGridLayout *editorLayout=new QGridLayout(this);
    editorLayout->setSpacing(0);
    editorLayout->addWidget(editorTabs);
    editorLayout->setContentsMargins(5,5,0,0);
    this->showMaximized();
    editorTabs->addTab(currentEditor,"New");
    currentFile="";

    connect(editorTabs,&QTabWidget::currentChanged,this,&Editor::tabChange);
    connect(editorTabs,&QTabWidget::tabCloseRequested,this,&Editor::tabClose);
    connect(currentEditor,&QsciScintilla::cursorPositionChanged,this,&Editor::editorCursorChanged);
   // currentEditor->set


}

void Editor::initializeEditor()

  {

      // codes based from http://eli.thegreenplace.net/2011/04/01/sample-using-qscintilla-with-pyqt/

      initializeFont();

      initializeMargin();

      initializeCaretLine();

      initializeLexer();

      // code based on QSciTE https://code.google.com/p/qscite/

      initializeFolding();

  }


void Editor::initializeFont()

{

    QFont font("Courier", 12);

    font.setFixedPitch(true);

    currentEditor->setFont(font);

}

void Editor::initializeMargin()

{

    QFontMetrics fontmetrics = QFontMetrics(currentEditor->font());

    currentEditor->setMarginsFont(currentEditor->font());

    currentEditor->setMarginWidth(0, fontmetrics.width(QString::number(currentEditor->lines())) + 20);

    currentEditor->setMarginLineNumbers(0, true);

    currentEditor->setMarginsBackgroundColor(QColor("#cccccc"));



   // connect(editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

}
void Editor::initializeLexer()

  {

      QsciLexerCPP *lexer = new QsciLexerCPP();

      lexer->setDefaultFont(currentEditor->font());

      lexer->setFoldComments(true);

      currentEditor->setLexer(lexer);

  }


void Editor::initializeCaretLine()

{

    // Current line visible with special background color

    currentEditor->setCaretLineVisible(true);

    currentEditor->setCaretLineBackgroundColor(QColor("#ffe4e4"));

}

void Editor::initializeFolding()

{

    QsciScintilla::FoldStyle state =

            static_cast<QsciScintilla::FoldStyle>((!currentEditor->folding()) * 5);

    if (!state)

        currentEditor->foldAll(false);

    currentEditor->setFolding(state);

}

void Editor::openFile(QString filename)
{
    QFile file(filename);
    ;
    if(file.open(QIODevice::ReadOnly))
    {
        QFileInfo fileInfo(file);

        if(!(currentFile.isEmpty()&&currentEditor->text().isEmpty()))
        {
            currentEditor=new QsciScintilla(this);
            initializeEditor();
            connect(currentEditor,&QsciScintilla::cursorPositionChanged,this,&Editor::editorCursorChanged);

        }

        editorTabs->addTab(currentEditor,fileInfo.fileName());
         editorTabs->setCurrentWidget(currentEditor);

        currentEditor->setText(file.readAll());

        file.close();
    }

}
void Editor::newFile()
{
    currentEditor->clear();
    currentFile="";
}

void Editor::undo()
{
    currentEditor->undo();
}

void Editor::redo()
{
    currentEditor->redo();
}

void Editor::copy()
{
    currentEditor->copy();
}

void Editor::paste()
{
    currentEditor->paste();
}

void Editor::cut()
{
    currentEditor->cut();
}

void Editor::del()
{
   // currentEditor->delete_selection();
   // currentEditor->de
}


void Editor::selectAll()
{
    currentEditor->selectAll();
}


void Editor::save()
{
    save(currentFile);
    currentEditor->setModified(false);
}

void Editor::save(QString name)
{
    QFile file(name);
    if(file.open(QIODevice::WriteOnly))
    {
       // file<<currentEditor->text();
       // file.write(currentEditor->text());
        QTextStream stream(&file);
        stream<<currentEditor->text();
        file.flush();
        file.close();
    }
}

void Editor::saveAs(QString name)
{
    currentFile=name;
    save();

}

void Editor::saveCopy(QString name)
{

    save(name);
}

void Editor::close()
{
    if(currentEditor->isModified())
    {
        QMessageBox msg(this);
        msg.setText("The document has been modified.");
        msg.setInformativeText("Do you want to save your changes?");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Save);

        int ret = msg.exec();

    }
    else
    {
        newFile();
    }

}

void Editor::tabChange(int i)
{
    currentEditor=(QsciScintilla*)editorTabs->widget(i);
}

void Editor::tabClose(int i)
{
    editorTabs->removeTab(i);
    if(editorTabs->count()==0)
    {
       currentEditor=new QsciScintilla(this);
        initializeEditor();
    editorTabs->addTab(currentEditor,"New");
     editorTabs->setCurrentWidget(currentEditor);

    }
}

void Editor::editorCursorChanged(int l,int c)
{
    qDebug()<<l<<" "<<c ;
    emit cursorChanged(l,c);

}
