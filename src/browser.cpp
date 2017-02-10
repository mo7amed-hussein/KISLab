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
#include "browser.h"
#include<QGridLayout>
#include<QFileInfo>
#include<QDebug>
#include <QApplication>
#include <QMenu>
#include <QMouseEvent>
#include<QAction>
#include<QDesktopServices>
Browser::Browser(QWidget *parent) : QWidget(parent)
{

    filesTree=new QTreeWidget(this);
    filesTree->setContextMenuPolicy(Qt::CustomContextMenu);
    filesTree->setHeaderHidden(true);
    filesTree->setColumnCount(1);


    QGridLayout *browserLayout=new QGridLayout(this);
    browserLayout->setSpacing(0);
    browserLayout->addWidget(filesTree);
    browserLayout->setContentsMargins(0,5,5,0);

    filesRoot=new QTreeWidgetItem(filesTree);
    filesRoot->setText(0,"Files");
    const QIcon openIcon=QIcon::fromTheme("document-open",QIcon(":/images/icons/open.png"));
    filesRoot->setIcon(0,openIcon);
    filesRoot->setExpanded(true);

    connect(filesTree,&QTreeWidget::itemDoubleClicked,this,&Browser::itemDClicked);
    connect(filesTree,&QTreeWidget::customContextMenuRequested,this,&Browser::onCustomContextMenuRequested);

}
void Browser::addfile(QString name, QString desc="")
{



    QTreeWidgetItem * item=new QTreeWidgetItem;
    item->setText(0,name);
    item->setText(1,desc);

    const QIcon newIcon=QIcon::fromTheme("document-new",QIcon(":/images/icons/new.png"));
    item->setIcon(0,newIcon);
    filesRoot->addChild(item);
}
void Browser::itemDClicked(QTreeWidgetItem * item, int column)
{
   // qDebug()<<item->text(1);
    emit showFile(item->text(1));
}

void Browser::onCustomContextMenuRequested(const QPoint& pos)
{
    QTreeWidgetItem * item=filesTree->itemAt(pos);

    if(item && item!= filesRoot)
    {
       // qDebug()<<item->text(0);
        showContextMenu(item,QWidget::mapToGlobal(pos));
    }

}

void Browser::showContextMenu(QTreeWidgetItem * item,const QPoint& gPos)
{
    QMenu menu;

    QAction *openAction=new QAction(tr("open"),this);
    QAction *folderAction=new QAction(tr("Show Containing Folder"),this);
    QAction *removeAction=new QAction(tr("Remove"),this);
    QAction *removeAllAction=new QAction(tr("Remove All"),this);
    QAction *removeButAction=new QAction(tr("Remove All But This"),this);

    itemPopup=item;

    connect(openAction,&QAction::triggered,this,&Browser::showFileAction);
    connect(removeAction,&QAction::triggered,this,&Browser::removefile);
    connect(folderAction,&QAction::triggered,this,&Browser::openFolder);
    connect(removeButAction,&QAction::triggered,this,&Browser::removeAllBut);
    connect(removeAllAction,&QAction::triggered,this,&Browser::removeAll);

    menu.addAction(openAction);
    menu.setDefaultAction(openAction);
    menu.addAction(removeAction);
    menu.addAction(removeAllAction);
    menu.addAction(removeButAction);
    menu.addAction(folderAction);
    menu.exec(gPos);

}
void Browser::showFileAction()
{
    showFile(itemPopup->text(1));

}

void Browser::removefile()
{
    filesRoot->removeChild(itemPopup);
    emit closeFile(itemPopup->text(0),itemPopup->text(1));
}
void Browser::openFolder()
{
    QString file=itemPopup->text(1);

    if(!file.isEmpty())
    {
        QFileInfo f(file);
    QDesktopServices::openUrl(QUrl(f.path()));
    }
}
void Browser::changeFilename(QString oldname,QString oldPath,QString newPath)
{
    int count=filesRoot->childCount();
    //qDebug()<<"filename changed"<<oldname<<oldPath<<newPath<<count;

    while(count--)
    {
        QTreeWidgetItem * item=filesRoot->child(count);
      //  qDebug()<<"child "<<count<<item->text(0)<<item->text(1);

        if(item->text(0)==oldname&&item->text(1)==oldPath)
        {
           QFileInfo f(newPath);
           item->setText(0,f.fileName());
           item->setText(1,newPath);
           return;
        }
    }

}

void Browser::removeChild(QString name,QString path)
{
    int count=filesRoot->childCount();
    //qDebug()<<"remove file"<<name<<path<<count;

    while(count--)
    {
        QTreeWidgetItem * item=filesRoot->child(count);
      //  qDebug()<<"child "<<count<<item->text(0)<<item->text(1);

        if(item->text(0)==name&&item->text(1)==path)
        {
           filesRoot->removeChild(item);
           return;
        }
    }


}

bool Browser::checkOpenedFile(QString name,QString path)
{
    int count=filesRoot->childCount();
    // qDebug()<<"remove file"<<name<<path<<count;

        while(count--)
        {
            QTreeWidgetItem * item=filesRoot->child(count);
      //      qDebug()<<"child "<<count<<item->text(0)<<item->text(1);

            if(item->text(0)==name&&item->text(1)==path)
            {

               return true;
            }
        }

return false;

}

void Browser::removeAll()
{
    int count=filesRoot->childCount();

        while(count--)
        {
            QTreeWidgetItem * item=filesRoot->child(count);
            itemPopup=item;
            removefile();
        }

}

void Browser::removeAllBut()
{
    int count=filesRoot->childCount();
      QTreeWidgetItem * currentItem=itemPopup;
    qDebug()<<currentItem->text(0);
        while(count--)
        {
            QTreeWidgetItem * item=filesRoot->child(count);
            if(item!=currentItem)
            {
        //    qDebug()<<"remove"<<item->text(0);
            itemPopup=item;
            removefile();
            }
        }

}
