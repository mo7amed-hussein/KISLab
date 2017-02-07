#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QObject>
#include<QWidget>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscistyledtext.h>
#include <Qsci/qscistyle.h>
#include<QString>
#include<QDateTime>
class TextEditor : public QsciScintilla
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = 0);
    ~TextEditor();

    void initializeEditor();
    void initializeLexer();
    void initializeFolding();
    void initializeMargin();
    void initializeCaretLine();
    void initializeFont();
    void setFileName(QString f);
    void setFileFullPath(QString p);
    void setLastModified(QDateTime lm);

    QString getFileName();
    QString getFileFullPath();
    QDateTime getLastModified();


signals:

public slots:

 private:
 QString *filename;
 QString *fileFullPath;
 QDateTime * lastModified;

};

#endif // TEXTEDITOR_H
