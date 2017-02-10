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
#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent) : QsciScintilla(parent)
{
    initEditor();
    filename=new QString();
    fileFullPath=new QString();
    lastModified=new QDateTime();
    this->setAcceptDrops(false);
    changeFlag=false;
    readonly=false;
    setModified(false);
    this->setUtf8(true);
}

TextEditor::~TextEditor()
{
    delete filename;
    delete fileFullPath;
}

void TextEditor::initEditor()

  {

    this->setMarginLineNumbers(0, true);

    this->setMarginsBackgroundColor(QColor("#cccccc"));

    this->setCaretLineVisible(true);

    this->setCaretLineBackgroundColor(QColor("#ffe4e4"));

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


bool TextEditor::isChanged()
{
    return changeFlag;

}

void TextEditor::setChanged(bool b)
{
 changeFlag=b;
}

bool TextEditor::checkReadOnly()
{
    return readonly;
}

void TextEditor::fileReadOnly()
{
    readonly=true;
}
