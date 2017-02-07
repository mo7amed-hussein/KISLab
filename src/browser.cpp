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
    //fileList=new QListWidget(this);
    //fileList->addItem("mm");
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

    QFileInfo f(name);

    QTreeWidgetItem * item=new QTreeWidgetItem;

    item->setText(0,f.fileName());
    item->setText(1,name);

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
    QAction *removeAction=new QAction(tr("remove"),this);
    itemPopup=item;
    connect(openAction,&QAction::triggered,this,&Browser::showFileAction);
    connect(removeAction,&QAction::triggered,this,&Browser::removefile);
    connect(folderAction,&QAction::triggered,this,&Browser::openFolder);

    menu.addAction(openAction);
    menu.setDefaultAction(openAction);
    menu.addAction(folderAction);
    menu.addAction(removeAction);
    menu.exec(gPos);

}
void Browser::showFileAction()
{
    showFile(itemPopup->text(1));

}

void Browser::removefile()
{
    filesRoot->removeChild(itemPopup);
    closeFile(itemPopup->text(1));
}
void Browser::openFolder()
{
    QString file=itemPopup->text(1);
    QFileInfo f(file);
    QDesktopServices::openUrl(QUrl(f.path()));

}
