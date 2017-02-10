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
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QObject>
#include<QWidget>
#include <Qsci/qsciscintilla.h>
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

    void initEditor();
    void setFileName(QString f);
    void setFileFullPath(QString p);
    void setLastModified(QDateTime lm);
    bool isChanged();
    void setChanged(bool b);
    QString getFileName();
    QString getFileFullPath();
    QDateTime getLastModified();
    bool checkReadOnly();
    void fileReadOnly();


signals:

public slots:

 private:
 QString *filename;
 QString *fileFullPath;
 QDateTime * lastModified;
 bool changeFlag;
 bool readonly;

};

#endif // TEXTEDITOR_H
