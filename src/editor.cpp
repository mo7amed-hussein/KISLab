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
#include "editor.h"
#include <QGridLayout>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileInfo>
#include<QDebug>
#include<QTabBar>
#include<QMenu>
#include<QAction>
#include<QInputDialog>
#include<QColor>
#include<timedialog.h>
#include<QStatusBar>
#include<QApplication>
#include<QSettings>
Editor::Editor(QWidget *parent) : QWidget(parent)
{

    newCount=1;

    isReload=QMessageBox::Yes;

    lexerFactory=new LexerFactory;

    fontFamily="Courier";
    fontSize=14;

    newFilename.append(tr("New %1").arg(newCount));

    findWidget=new FindWidget;
    findWidget->hide();

    editorTabs=new QTabWidget(this);
    editorTabs->setContextMenuPolicy(Qt::CustomContextMenu);
    editorTabs->setTabsClosable(true);

    QGridLayout *editorLayout=new QGridLayout(this);
    editorLayout->setSpacing(0);
    editorLayout->addWidget(editorTabs);
    editorLayout->addWidget(findWidget);
    editorLayout->setContentsMargins(5,5,0,0);
    this->showMaximized();

    connect(findWidget,&FindWidget::findWidgetclosed,this,&Editor::closeFindWidget);
    connect(findWidget,&FindWidget::findNxtSig,this,&Editor::findNxtSlot);
    connect(findWidget,&FindWidget::replaceSig,this,&Editor::replace);
    connect(editorTabs,&QTabWidget::currentChanged,this,&Editor::tabChange);
    connect(editorTabs,&QTabWidget::tabCloseRequested,this,&Editor::tabClose);
    connect(editorTabs,&QTabWidget::customContextMenuRequested,this,&Editor::onCustomContextMenuRequested);

    updateSetting();
}



void Editor::openFile(QString filename)
{
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly|QFile::Text))
    {
        QFileInfo fileInfo(file);

        if(!(currentEditor->getFileFullPath().isEmpty()&&currentEditor->text().isEmpty()))
        {
            currentEditor=new TextEditor(this);

            connect(currentEditor,&TextEditor::cursorPositionChanged,this,&Editor::editorCursorChanged);
            connect(currentEditor,&TextEditor::copyAvailable,this,&Editor::copyChangedSlot);
            connect(currentEditor,&TextEditor::modificationChanged,this,&Editor::fileChangedSlot);

            editorTabs->addTab(currentEditor,fileInfo.fileName());
        }
        else
        {
            newFilename.append(currentEditor->getFileName());
            emit removeFile(currentEditor->getFileName(),currentEditor->getFileFullPath());
        }

        if(editorTabs->count()==1)
          {
            emit noFilesChanged(false);
           }

        QString title;
        title=fileInfo.fileName();

        if(!fileInfo.isWritable())
        {
            title+=" [Read-Only]";
            currentEditor->fileReadOnly();
        }

        editorTabs->setTabText(editorTabs->indexOf(currentEditor),title);
        editorTabs->setCurrentWidget(currentEditor);

        initTextEditor(currentEditor,fileInfo.fileName());

        currentEditor->setFileName(fileInfo.fileName());
        currentEditor->setFileFullPath(filename);
        currentEditor->setLastModified(fileInfo.lastModified());
        currentEditor->setChanged(true);
        currentEditor->setText(file.readAll());
        currentEditor->setModified(false);
        currentEditor->setChanged(false);

        emit fileChangedSig(false);

        file.close();
    }

}
QString Editor::newFile()
{

    currentEditor=new TextEditor(this);

    QString name=newFilename.takeLast();

    editorTabs->addTab(currentEditor,name);

    currentEditor->setFileName(name);
    currentEditor->setFileFullPath("");

   if(newFilename.size()==0)
   {
     newCount++;
     newFilename.append(tr("New %1").arg(newCount));
   }

   editorTabs->setCurrentWidget(currentEditor);
   emit fileChangedSig(false);

   connect(currentEditor,&TextEditor::cursorPositionChanged,this,&Editor::editorCursorChanged);
   connect(currentEditor,&TextEditor::copyAvailable,this,&Editor::copyChangedSlot);
   connect(currentEditor,&TextEditor::modificationChanged,this,&Editor::fileChangedSlot);

  if(editorTabs->count()==1)
    { 
      emit noFilesChanged(false);
     }

  return name;
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
    currentEditor->removeSelectedText();
}


void Editor::selectAll()
{
    currentEditor->selectAll();
}


bool Editor::save()
{
    return save(currentEditor);
}

bool Editor::save(QString name)
{
    if(name.isEmpty())
    {
      emit fileIsNew();

    }
    else
    {
        QFile file(name);
        if(file.open(QIODevice::WriteOnly))
            {

                QTextStream stream(&file);
                stream<<currentEditor->text();
                file.flush();
                file.close();
                return true;

             }
    }

    return false;
}

bool Editor::saveAs(QString name)
{
    if(currentEditor->getFileFullPath().isEmpty())
    {
        newFilename.append(currentEditor->getFileName());
    }

    emit filenameChanged(currentEditor->getFileName(),currentEditor->getFileFullPath(),name);

    if(save(name))
    {

        currentEditor->setFileFullPath(name);

        QFileInfo f(name);

        currentEditor->setFileName(f.fileName());
        currentEditor->setModified(false);
        currentEditor->setChanged(false);

        editorTabs->setTabText(editorTabs->indexOf(currentEditor),f.fileName());

        updateLastModified(currentEditor);

        return true;
    }

return false;
}

void Editor::saveCopy(QString name)
{

    save(name);
}

bool Editor::close()
{
   return close(currentEditor);
}

void Editor::tabChange(int i)
{
   if(editorTabs->count()>0)
   {
     currentEditor=(TextEditor*)editorTabs->widget(i);
     emit fileChangedSig(currentEditor->isModified());
   // qDebug()<<currentEditor->getFileName()<<" ,"<<currentEditor->getFileFullPath();
   }
}

bool Editor::tabClose(int i)
{
   TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(i);

   return close(tmpEditor);
}

void Editor::editorCursorChanged(int l,int c)
{
  //  qDebug()<<l<<" "<<c ;
    emit cursorChanged(l,c);

}

bool Editor::closeAll()
{
   int count=editorTabs->count();

   bool isClosed=true;

   while(count--)
   {
       if(!tabClose(count))
         {
            isClosed=false;
         }
   }

   return isClosed;
}

void Editor::closeFindWidget()
{
   // qDebug()<<"clicked";
    findWidget->hide();
}
void Editor::showFindWidget()
{
  findWidget->show();
}

void Editor::findNxtSlot(const QString &expr,bool re,bool cs,bool wo,bool wrap)
{

      currentEditor->findFirst(expr,re,cs,wo,wrap);
}

void Editor::saveAll()
{
    int count=editorTabs->count();

    while(count--)
       {
           currentEditor=(TextEditor*)editorTabs->widget(count);

           editorTabs->setCurrentIndex(count);

           save();

       }

}
void Editor::showDoc(QString filePath)
{
    int count=editorTabs->count();

    while(count--)
       {
           TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(count);

           if(tmpEditor->getFileFullPath()==filePath)
            {
               editorTabs->setCurrentIndex(count);
               return;
            }

       }

       openFile(filePath);
}

bool Editor::closeFile(QString filename,QString filePath)
{
    int count=editorTabs->count();

    while(count--)
    {
        TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(count);

        if(tmpEditor->getFileFullPath()==filePath&&tmpEditor->getFileName()==filename)
        {
            tabClose(count);
            return true;
        }

    }
    return false;
}

 void Editor::onCustomContextMenuRequested(const QPoint& pos)
 {
     QTabBar * tab=editorTabs->tabBar();

     int index=tab->tabAt(pos);
    // qDebug()<<"clicked tab"<<index;

     if(index>-1)
     {
             QMenu menu;
             clickedTab=index;
             QAction *closeAction=new QAction(tr("Close"),this);
             QAction *closeallAction=new QAction(tr("Close all but this"),this);
             QAction *saveAction=new QAction(tr("Save"),this);

             connect(closeAction,&QAction::triggered,this,&Editor::closeTabContext);
             connect(closeallAction,&QAction::triggered,this,&Editor::closeAllTabContext);
             connect(saveAction,&QAction::triggered,this,&Editor::saveTabContext);

             menu.addAction(closeAction);
             menu.addAction(closeallAction);
             menu.addAction(saveAction);
             menu.exec(QWidget::mapToGlobal(pos));
     }

 }

void Editor::closeTabContext()
 {

    tabClose(clickedTab);

 }

void Editor::closeAllTabContext()
{
    int count=editorTabs->count();

    while(count--)
    {
        if(count!=clickedTab)
        {
           tabClose(count);
        }
    }

}
void Editor::saveTabContext()
  {
      TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(clickedTab);

      save(tmpEditor->getFileFullPath());
  }

void Editor::goLine()
{
    bool ok;
     int line=QInputDialog::getInt(this,tr("Go To Line"),tr("Line"),0,0,currentEditor->lines(),1,&ok,Qt::Popup);
     if(ok)
     {
         line--;

        currentEditor->ensureLineVisible(line);
        currentEditor->setCursorPosition(line,0);
        currentEditor->setFocus();
     }
}

void Editor::toLowerCase()
{
    if(currentEditor->hasSelectedText())
    {

    QString str=currentEditor->selectedText();

    currentEditor->replaceSelectedText(str.toLower());
    }
}

void Editor::toUpperCase()
{
    if(currentEditor->hasSelectedText())
    {
    QString str=currentEditor->selectedText();

    currentEditor->replaceSelectedText(str.toUpper());
    }
 }

void Editor::timeStamp()
{

int line,col;

TimeDialog timeDialog(this);

QString txt=timeDialog.getFormat();


if(!txt.isEmpty())
{

    currentEditor->getCursorPosition(&line,&col);
    currentEditor->insertAt(txt,line,col);
}
}

QString Editor::getCurrentFilePath()
{
    return currentEditor->getFileFullPath();

}
void Editor::fileStatDiag()
{
    QString txt=currentEditor->text();
    int charsGros=txt.size()-txt.count('\n');

    int lines=currentEditor->lines();

    int bytes=txt.size();

    int charsNet=charsGros-txt.count(' ');

    int words=0;

   for(int i=1;i<bytes;i++)
   {
       if((txt.at(i)==' ')&&(txt.at(i-1)!=' '))
       {
           words++;
       }
       if((txt.at(i)=='\n')&&(txt.at(i-1)!='\n'))
       {
           words++;
       }
   }


    QMessageBox msg(this);

    msg.setWindowTitle(currentEditor->getFileName());
    msg.setText(tr("<b>Lines             :</b> %1"
                "<p><b>Words             :</b> %2"
                "<p><b>Characters(gross) :</b> %3"
                "<p><b>Characters(net)   :</b> %4"
                "<p><b>Bytes             :</b> %5").arg(lines).arg(words).arg(charsGros).arg(charsNet).arg(bytes));
    msg.exec();
   // qDebug()<<charsGros<<lines<<charsNet<<words<<bytes;

}
void Editor::copyChangedSlot(bool c)
{
    emit copyChangedSig(c);
}
bool Editor::isUndoAvailable()
{
 return currentEditor->isUndoAvailable();
}

bool Editor::isRedoAvailable()
{
 return currentEditor->isRedoAvailable();
}

void Editor::fileChangedSlot(bool s)
{
   // qDebug()<<"modified flag is "<<s <<"and change is "<<currentEditor->isChanged();
    if((!currentEditor->isChanged())&&s)
    {
        QString title=editorTabs->tabText(editorTabs->currentIndex());
        title.insert(0,'*');

        currentEditor->setChanged(true);

        editorTabs->setTabText(editorTabs->currentIndex(),title);
    }

    emit fileChangedSig(s);
}
void Editor::replace(const QString &replaceStr)
{
    currentEditor->replace(replaceStr);
}

bool Editor::close(TextEditor *tmp)
{
    bool isClosed=true;
    if(tmp->isModified())
    {
        QMessageBox msg(this);
        msg.setText(tr("\" %1 \" document has been modified.").arg(tmp->getFileName()));
        msg.setInformativeText("Do you want to save your changes?");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Save);
        msg.setWindowTitle(tr("%1").arg(tmp->getFileName()));

        int ret = msg.exec();
        switch (ret) {
            case QMessageBox::Save:
                        save();
                        editorTabs->removeTab(editorTabs->indexOf(tmp));
                        break;
            case QMessageBox::Discard:
                        //don't save
                        if(tmp->getFileFullPath().isEmpty())
                        {
                            emit removeFile(tmp->getFileName(),tmp->getFileFullPath());
                            newFilename.append(tmp->getFileName());

                        }
                        editorTabs->removeTab(editorTabs->indexOf(tmp));
                        break;
            case QMessageBox::Cancel:
                    isClosed=false;
                    break;
            default:
                    break;
        }

    }
    else
    {

        if(tmp->getFileFullPath().isEmpty())
        {
            emit removeFile(tmp->getFileName(),tmp->getFileFullPath());
            newFilename.append(tmp->getFileName());
        }

        editorTabs->removeTab(editorTabs->indexOf(tmp));

    }

    if(editorTabs->count()==0)
      {
        emit noFilesChanged(true);
      }

    return isClosed;

}

bool Editor::save(TextEditor *tmp)
{
    if(tmp->getFileFullPath().isEmpty()||tmp->checkReadOnly())
    {
        //emit fileIsNew();

    }
    else
    {

        QFile file(tmp->getFileFullPath());

       if(file.open(QIODevice::WriteOnly))
          {
                int index=editorTabs->indexOf(tmp);

                QTextStream stream(&file);
                stream<<tmp->text();

                file.flush();
                file.close();

                tmp->setModified(false);

                QString title=editorTabs->tabText(index);
                title.remove(0,1);

                tmp->setChanged(false);

                editorTabs->setTabText(index,title);

                updateLastModified(tmp);

                return true;

            }

    }
return false;
}

void Editor::updateLastModified(TextEditor *tmp)
{
    if(!tmp)
    {
        QFileInfo f(tmp->getFileFullPath());
        tmp->setLastModified(f.lastModified());
    }
}

void Editor::autoSaveAll()
{
   int count=editorTabs->count();
    while(count--)
    {
        TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(count);
        if(!tmpEditor->getFileFullPath().isEmpty() && tmpEditor->isModified())
        {
            save(tmpEditor);
          //  qDebug()<<tmpEditor->getFileName()<<" saved";
        }

    }

}


void Editor::checkExternalChange()
{
    int count=editorTabs->count();
    while(count--)
    {
        TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(count);
        if(!tmpEditor->getFileFullPath().isEmpty())
        {
            QFileInfo f(tmpEditor->getFileFullPath());
            //qDebug()<<f.fileName()<<" changed";
            QDateTime current=f.lastModified();

            if(current != tmpEditor->getLastModified() && isReload!=QMessageBox::NoToAll)
            {
                askToReload(tmpEditor);
            }
        }

    }

    isReload=QMessageBox::Yes;
}
void Editor::askToReload(TextEditor *tmp)
{

    if(isReload !=QMessageBox::YesToAll)
    {
        QMessageBox msg;
        msg.setText(tr("\' %1 \' has been changed.").arg(tmp->getFileName()));
        msg.setInformativeText(tr("Do you want to reload it ?"));
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No |QMessageBox::YesToAll|QMessageBox::NoToAll);
        isReload=msg.exec();
    }

    if(isReload==QMessageBox::Yes ||isReload==QMessageBox::YesToAll )
    {
    QFile file(tmp->getFileFullPath());
    QFileInfo fileInfo(tmp->getFileFullPath());

    editorTabs->setCurrentWidget(tmp);

    if(file.open(QIODevice::ReadOnly|QFile::Text))
    {
        tmp->setChanged(true);
        tmp->clear();
        tmp->setLastModified(fileInfo.lastModified());

        tmp->setText(file.readAll());
        tmp->setModified(false);
        tmp->setChanged(false);
        file.close();

    }

    }


}

 void Editor::initTextEditor(TextEditor *tmp,QString filename)
 {
     QString fileType=lexerFactory->getFileType(filename);
   // qDebug()<<">>>>> "<<fileType;

    QFont font(fontFamily,fontSize);
    font.setFixedPitch(true);

    tmp->setFont(font);

    QFontMetrics fontmetrics = QFontMetrics(font);

    tmp->setMarginsFont(font);
    tmp->setMarginWidth(0, fontmetrics.width(QString::number(tmp->lines())) + 25);

    QsciLexer *lexer=lexerFactory->getLexer(fileType);
     if(lexer != NULL)
     {
         lexer->setDefaultFont(this->font());
         lexer->setFont(font);

         tmp->setLexer(lexer);
     }

     tmp->autoCompleteFromAll();
     tmp->setAutoCompletionSource(QsciScintilla::AcsAll);
     tmp->setAutoCompletionThreshold(3);
 }

void Editor::updateSetting()
{
    QSettings set;

    fontSize=set.value("FONT_SIZE",14).toInt();

    fontFamily=set.value("FONT","Courier").toString();

    QFont font(fontFamily,fontSize);

    int count=editorTabs->count();

    while(count--)
     {
         TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(count);

         tmpEditor->setFont(font);

         if(tmpEditor->lexer()!= 0)
         {

         tmpEditor->lexer()->setFont(font);

         }

         QFontMetrics fontmetrics = QFontMetrics(font);

         tmpEditor->setMarginsFont(font);

         tmpEditor->setMarginWidth(0, fontmetrics.width(QString::number(tmpEditor->lines())) + 25);

     }

}
