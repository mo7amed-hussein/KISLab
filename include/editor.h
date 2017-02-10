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
#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTabWidget>
//#include <Qsci/qsciscintilla.h>
#include <QList>
#include "findwidget.h"
#include "texteditor.h"
#include"lexerfactory.h"

class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);


    void openFile(QString filetxt);
    QString newFile();
    void undo();
    void redo();
    void copy();
    void paste();
    void cut();
    void del();
    void selectAll();
    bool save();
    bool save(QString name);
    bool save(TextEditor *tmp);
    bool saveAs(QString name);
    void saveCopy(QString name);
    void saveAll();


    bool close();
    bool close(TextEditor *tmp);
    bool closeFile(QString filename,QString filePath);
    bool closeAll();

    void goLine();
    void toLowerCase();
    void toUpperCase();
    void timeStamp();
    void showFindWidget();
    QString getCurrentFilePath();
    bool isUndoAvailable();
    bool isRedoAvailable();
    void fileStatDiag();
    void updateLastModified(TextEditor *tmp);
    void autoSaveAll();
    void checkExternalChange();
    void askToReload(TextEditor *tmp);
    void initTextEditor(TextEditor *tmp,QString filename);
    void updateSetting();

signals:

    void cursorChanged(int l,int c);
    void fileIsNew();
    void copyChangedSig(bool c);
    void fileChangedSig(bool s);
    void filenameChanged(QString oldname,QString oldPath,QString newPath);
    void removeFile(QString name,QString path);
    void emptySig();
    void noFilesChanged(bool f);
public slots:
    void tabChange(int i);
    bool tabClose(int i);
    void closeTabContext();
    void closeAllTabContext();
    void saveTabContext();
    void editorCursorChanged(int l,int c);
    void closeFindWidget();
    void findNxtSlot(const QString &expr,bool re,bool cs,bool wo,bool wrap);
    void showDoc(QString filePath);
    void onCustomContextMenuRequested(const QPoint& pos);
    void copyChangedSlot(bool c);
    void fileChangedSlot(bool s);
    void replace(const QString &replaceStr);
private:
    TextEditor *currentEditor;
    QString currentFile;
    LexerFactory *lexerFactory;
    QTabWidget *editorTabs;
    QStringList newFilename;
    FindWidget *findWidget;
    QString fontFamily;
    int fontSize;
    int newCount;
    int clickedTab;
    int isReload;
};

#endif // EDITOR_H
