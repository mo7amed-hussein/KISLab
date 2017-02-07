#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent) : QsciScintilla(parent)
{
    initializeEditor();
    filename=new QString();
    fileFullPath=new QString();
    lastModified=new QDateTime();
    this->setAcceptDrops(false);
}

TextEditor::~TextEditor()
{
    delete filename;
    delete fileFullPath;
}

void TextEditor::initializeEditor()

  {

      // codes based from http://eli.thegreenplace.net/2011/04/01/sample-using-qscintilla-with-pyqt/

      initializeFont();

      initializeMargin();

      initializeCaretLine();

      initializeLexer();

      // code based on QSciTE https://code.google.com/p/qscite/

      initializeFolding();

  }


void TextEditor::initializeFont()

{

    QFont font("Courier", 14);

    font.setFixedPitch(true);

    this->setFont(font);

}

void TextEditor::initializeMargin()

{

    QFontMetrics fontmetrics = QFontMetrics(this->font());

    this->setMarginsFont(this->font());

    this->setMarginWidth(0, fontmetrics.width(QString::number(this->lines())) + 25);

    this->setMarginLineNumbers(0, true);

    this->setMarginsBackgroundColor(QColor("#cccccc"));



   // connect(TextEditor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

}
void TextEditor::initializeLexer()

  {

      QsciLexerCPP *lexer = new QsciLexerCPP();

      lexer->setDefaultFont(this->font());


      lexer->setFoldComments(true);

      this->setLexer(lexer);
      this->autoCompleteFromAll();
      this->setAutoCompletionSource(AcsAll);
      this->setAutoCompletionThreshold(3);

     // QsciStyledText *newstyle=new QsciStyledText ("main",QsciStyle(12,"",QColor("#cccccc"),QColor("#cccccc"),this->font()));
      //newstyle->apply(this);
     // lexer->findChild("main",Qt::FindChildrenRecursively);


  }


void TextEditor::initializeCaretLine()

{

    // Current line visible with special background color

    this->setCaretLineVisible(true);

    this->setCaretLineBackgroundColor(QColor("#ffe4e4"));

}

void TextEditor::initializeFolding()

{

    QsciScintilla::FoldStyle state =

            static_cast<QsciScintilla::FoldStyle>((!this->folding()) * 5);

    if (!state)

        this->foldAll(false);

    this->setFolding(state);

}

void TextEditor::setFileName(QString f)
{
    if(!filename)
    {
        delete filename;
    }
    filename=new QString(f);
}

void TextEditor::setFileFullPath(QString p)
{
    if(!fileFullPath)
    {
        delete filename;
    }
    fileFullPath=new QString(p);
}

QString TextEditor::getFileName()
{
    return (*filename);
}

QString TextEditor::getFileFullPath()
{
    return (*fileFullPath);
}

QDateTime TextEditor::getLastModified()
{
    return (*lastModified);
}

void TextEditor::setLastModified(QDateTime lm)
{
    if(!lastModified)
    {
        delete lastModified;
    }
    lastModified=new QDateTime(lm);
}


