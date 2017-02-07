#include "editor.h"
//#include <Qsci/qscilexercpp.h>
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

Editor::Editor(QWidget *parent) : QWidget(parent)
{

    newCount=1;
    find=new FindDialog;
    find->hide();
   // find->setAttribute();

    editorTabs=new QTabWidget(this);
    editorTabs->setContextMenuPolicy(Qt::CustomContextMenu);

    editorTabs->setTabsClosable(true);
    QGridLayout *editorLayout=new QGridLayout(this);
    editorLayout->setSpacing(0);
    editorLayout->addWidget(editorTabs);
    editorLayout->addWidget(find);
    editorLayout->setContentsMargins(5,5,0,0);
    this->showMaximized();
    //editorTabs->addTab(currentEditor,"New");
    currentFile="";
    newFile();


 //   editorTabs->setCornerWidget(find,Qt::BottomRightCorner);
   // editorLayout->addWidget(find);

    connect(find,&FindDialog::findDialogclosed,this,&Editor::closeFindDialog);
    connect(find,&FindDialog::findNxtSig,this,&Editor::findNxtSlot);
    connect(find,&FindDialog::replaceSig,this,&Editor::replace);

    connect(editorTabs,&QTabWidget::currentChanged,this,&Editor::tabChange);
    connect(editorTabs,&QTabWidget::tabCloseRequested,this,&Editor::tabClose);
    connect(editorTabs,&QTabWidget::customContextMenuRequested,this,&Editor::onCustomContextMenuRequested);


    // currentEditor->set


}



void Editor::openFile(QString filename)
{
    QFile file(filename);
    ;
    if(file.open(QIODevice::ReadOnly|QFile::Text))
    {
        QFileInfo fileInfo(file);

        if(!(currentFile.isEmpty()&&currentEditor->text().isEmpty()))
        {
            currentEditor=new TextEditor(this);
            //initializeEditor();
            connect(currentEditor,&TextEditor::cursorPositionChanged,this,&Editor::editorCursorChanged);
            connect(currentEditor,&TextEditor::copyAvailable,this,&Editor::copyChangedSlot);
            connect(currentEditor,&TextEditor::modificationChanged,this,&Editor::fileChangedSlot);

            //filesList.push_back(new QString(filename));
            editorTabs->addTab(currentEditor,fileInfo.fileName());
        }


        editorTabs->setTabText(editorTabs->indexOf(currentEditor),fileInfo.fileName());
        editorTabs->setCurrentWidget(currentEditor);
        currentEditor->setFileName(fileInfo.fileName());
        currentEditor->setFileFullPath(filename);
        currentEditor->setLastModified(fileInfo.lastModified());
        currentEditor->setText(file.readAll());
        currentEditor->setModified(false);
        emit fileChangedSig(false);
        file.close();
    }

}
void Editor::newFile()
{
    //currentEditor=new QsciScintilla(this);
    currentEditor=new TextEditor(this);
     //initializeEditor();
 editorTabs->addTab(currentEditor,tr("New %1").arg(newCount));
 newCount++;
  editorTabs->setCurrentWidget(currentEditor);
  currentFile="";
  currentEditor->setModified(false);
  emit fileChangedSig(false);
  connect(currentEditor,&TextEditor::cursorPositionChanged,this,&Editor::editorCursorChanged);
  connect(currentEditor,&TextEditor::copyAvailable,this,&Editor::copyChangedSlot);
  connect(currentEditor,&TextEditor::modificationChanged,this,&Editor::fileChangedSlot);

  //filesList.push_back(new QString(""));
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
    if(currentEditor->getFileName().isEmpty())
    {
        emit fileIsNew();

    }
    else
    {
    save(currentEditor->getFileFullPath());

    }
}

void Editor::save(QString name)
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
       // file<<currentEditor->text();
       // file.write(currentEditor->text());
        QTextStream stream(&file);
        stream<<currentEditor->text();
        file.flush();
        file.close();
        currentEditor->setModified(false);

    }
    }
}

void Editor::saveAs(QString name)
{
    //currentFile=name;
    currentEditor->setFileFullPath(name);
    QFileInfo f(name);
    currentEditor->setFileName(f.fileName());
    save();
    editorTabs->setTabText(editorTabs->indexOf(currentEditor),f.fileName());


}

void Editor::saveCopy(QString name)
{

    save(name);
}

bool Editor::close()
{

    bool isClosed=true;
    if(currentEditor->isModified())
    {
        QMessageBox msg(this);
        msg.setText(tr("\" %1 \" document has been modified.").arg(currentEditor->getFileName()));
        msg.setInformativeText("Do you want to save your changes?");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Save);
        msg.setWindowTitle(tr("%1").arg(currentEditor->getFileName()));
        int ret = msg.exec();
        switch (ret) {
        case QMessageBox::Save:
            save();
            editorTabs->removeTab(editorTabs->indexOf(currentEditor));
            break;
        case QMessageBox::Discard:
            //don't save
            editorTabs->removeTab(editorTabs->indexOf(currentEditor));
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
        editorTabs->removeTab(editorTabs->indexOf(currentEditor));

    }

    if(editorTabs->count()==0)
      {
           newFile();
        }
    return isClosed;
}

void Editor::tabChange(int i)
{
   if(editorTabs->count()>0)
   {
    currentEditor=(TextEditor*)editorTabs->widget(i);
    emit fileChangedSig(currentEditor->isModified());
    qDebug()<<currentEditor->getFileName()<<" ,"<<currentEditor->getFileFullPath();
   }
}

bool Editor::tabClose(int i)
{

    bool isClosed=true;
   // editorTabs->removeTab(i);
   TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(i);
   if(tmpEditor->isModified())
   {
       QMessageBox msg(this);
       msg.setText(tr("\" %1 \" document has been modified.").arg(tmpEditor->getFileName()));
       msg.setInformativeText("Do you want to save your changes?");
       msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
       msg.setDefaultButton(QMessageBox::Save);
        msg.setWindowTitle(tr("%1").arg(tmpEditor->getFileName()));
       int ret = msg.exec();
       switch (ret) {
       case QMessageBox::Save:
           save();
           editorTabs->removeTab(i);
           break;
       case QMessageBox::Discard:
           //don't save
           editorTabs->removeTab(i);
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
       qDebug()<<"remove file";
      editorTabs->removeTab(i);

   }
   if(editorTabs->count()==0)
     {
       qDebug()<<"new file";
          newFile();
      }
   return isClosed;
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

void Editor::closeFindDialog()
{
    qDebug()<<"clicked";
    find->hide();
}
void Editor::showFindDialog()
{
  find->show();
}

void Editor::findNxtSlot(const QString &expr,bool re,bool cs,bool wo,bool wrap)
{

      currentEditor->findFirst(expr,re,cs,wo,wrap);

   // currentEditor->setSelectionBackgroundColor(QColor(255,0,0,255));
    //currentEditor->setSelectionForegroundColor(QColor(0,255,0,255));
   // currentEditor->resetSelectionBackgroundColor();
   // currentEditor->resetSelectionForegroundColor();

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
bool Editor::closeFile(QString file)
{
    int count=editorTabs->count();
    while(count--)
    {
        TextEditor *tmpEditor=(TextEditor*)editorTabs->widget(count);
        if(tmpEditor->getFileFullPath()==file)
        {
            //editorTabs->removeTab(count);
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
     qDebug()<<"clicked tab"<<index;
     if(index>-1)
     {
             QMenu menu;
             clickedTab=index;
             QAction *closeAction=new QAction(tr("Close"),this);
             QAction *closeallAction=new QAction(tr("Close all but this"),this);
             QAction *saveAction=new QAction(tr("Save"),this);
             //itemPopup=item;
             connect(closeAction,&QAction::triggered,this,&Editor::closeTabContext);
             connect(closeallAction,&QAction::triggered,this,&Editor::closeAllTabContext);
             connect(saveAction,&QAction::triggered,this,&Editor::saveTabContext);

             //connect(removeAction,&QAction::triggered,this,&Browser::removefile);
             menu.addAction(closeAction);
            // menu.setDefaultAction(openAction);
             menu.addAction(closeallAction);
             menu.addAction(saveAction);
             menu.exec(QWidget::mapToGlobal(pos));
     }

 }

void Editor::closeTabContext(bool b)
 {
    //tabClose(clickedTab);
//currentEditor->annotate(3,"mohamed",1);
//currentEditor->fillIndicatorRange(2,4,6,7,1);

 }
void Editor::closeAllTabContext(bool b)
{
    int count=editorTabs->count();

    while(count--)
    {
        if(count!=clickedTab)
        {
           tabClose(count);
        }
    }
    ;
}
void Editor::saveTabContext(bool b)
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
 QDateTime d(QDate::currentDate(),QTime::currentTime());
int line,col;
currentEditor->getCursorPosition(&line,&col);
//qDebug()<<line <<col;
currentEditor->insertAt(d.toString(Qt::ISODate),line,col);
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
   // int ch=txt.count(' ');
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

    //QString msg;
    QMessageBox msg(this);
    msg.setWindowTitle(currentEditor->getFileName());
    msg.setText(tr("<b>Lines             :</b> %1"
                "<p><b>Words             :</b> %2"
                "<p><b>Characters(gross) :</b> %3"
                "<p><b>Characters(net)   :</b> %4"
                "<p><b>Bytes             :</b> %5").arg(lines).arg(words).arg(charsGros).arg(charsNet).arg(bytes));
    msg.exec();
    qDebug()<<charsGros<<lines<<charsNet<<words<<bytes;

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
    emit fileChangedSig(s);
}
void Editor::replace(const QString &replaceStr)
{
    currentEditor->replace(replaceStr);
}
