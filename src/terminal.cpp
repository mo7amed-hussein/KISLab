#include "terminal.h"
#include"Session.h"
#include<QApplication>
#include<QGridLayout>
#include<QMenu>
#include<QDebug>

Terminal::Terminal(QWidget *parent) : QWidget(parent)
{

    termLayout=new QGridLayout(this);

   // this->setLayout(termLayout);
    termLayout->setSpacing(0);
    //termLayout->addWidget(termWidget);
    termLayout->setContentsMargins(5,5,0,0);

     configTerm();




   copyAction=new QAction(tr("Copy"),this);
  // copyAction->setEnabled(false);
   pasteAction=new QAction(tr("Paste"),this);
    // connect(termWidget,SIGNAL(copyAvailable(bool)),this,SLOT(copyToggle(bool)));
   connect(pasteAction,&QAction::triggered,this,&Terminal::paste);
   connect(copyAction,&QAction::triggered,this,&Terminal::copy);


}

void Terminal::onCustomContextMenuRequested(const QPoint& pos)
{
    QMenu menu;


    QAction *searchAction=new QAction(tr("Search"),this);

   // itemPopup=item;
   // connect(openAction,&QAction::triggered,this,&Browser::showFileAction);
  connect(searchAction,&QAction::triggered,this,&Terminal::searchBarToggle);
    menu.addAction(copyAction);
    //menu.setDefaultAction(pasteAction);
    menu.addAction(pasteAction);
    menu.addAction(searchAction);
    menu.exec(QWidget::mapToGlobal(pos));
}
void Terminal::searchBarToggle(bool c)
{
    termWidget->toggleShowSearchBar();
}

void Terminal::copyToggle(bool c)
{

    qDebug()<<c<<"done";
     copyAction->setEnabled(c);

}
void Terminal::paste()
{
    termWidget->pasteClipboard();
}
void Terminal::copy()
{
    termWidget->copyClipboard();
}

void Terminal::getFocus()
{
    //qDebug()<<"focus";

}
void Terminal::terminalClosed()
{

    termLayout->removeWidget(termWidget);

    delete termWidget;
    configTerm();
    emit closeTerminaldock();

}
void Terminal::configTerm()
{
    termWidget=new QTermWidget(this);
    termWidget->setScrollBarPosition(QTermWidget::ScrollBarRight);
    termWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    termLayout->addWidget(termWidget);
   connect(termWidget,&QTermWidget::customContextMenuRequested,this,&Terminal::onCustomContextMenuRequested);
    connect(termWidget,&QTermWidget::termGetFocus,this,&Terminal::getFocus);
    connect(termWidget,&QTermWidget::copyAvailable,this,&Terminal::copyToggle);
    connect(termWidget,&QTermWidget::finished,this,&Terminal::terminalClosed);



}

void Terminal::toggleShow(bool s)
{
    if(s)
    {
        termWidget->startShellProgram();
    }
    else
    {
       // termLayout->removeWidget(termWidget);
        //termWidget-;
        //delete termWidget;
    }

}
