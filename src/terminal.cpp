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
#include "terminal.h"
#include"Session.h"
#include<QApplication>
#include<QGridLayout>
#include<QMenu>
#include<QDebug>
#include<QKeyEvent>
#include"ColorTables.h"

Terminal::Terminal(QWidget *parent) : QWidget(parent)
{

    termLayout=new QGridLayout(this);
    termLayout->setSpacing(0);
    termLayout->setContentsMargins(5,5,0,0);

    configTerm();

   copyAction=new QAction(tr("Copy"),this);
   pasteAction=new QAction(tr("Paste"),this);

   connect(pasteAction,&QAction::triggered,this,&Terminal::paste);
   connect(copyAction,&QAction::triggered,this,&Terminal::copy);


}

void Terminal::onCustomContextMenuRequested(const QPoint& pos)
{
    QMenu menu;

    QAction *searchAction=new QAction(tr("Search"),this);

    connect(searchAction,&QAction::triggered,this,&Terminal::searchBarToggle);

    menu.addAction(copyAction);
    menu.addAction(pasteAction);
    menu.addAction(searchAction);

    menu.exec(QWidget::mapToGlobal(pos));
}
void Terminal::searchBarToggle()
{
    termWidget->toggleShowSearchBar();
}

void Terminal::copyToggle(bool c)
{

   // qDebug()<<c<<"done";
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
    termWidget->setAutoFillBackground(true);
    termWidget->setFlowControlEnabled(false);
    termWidget->setFlowControlWarningEnabled(false);
    termWidget->setHistorySize(5000);
    termWidget->setScrollBarPosition(QTermWidget::ScrollBarRight);
    termWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    termLayout->addWidget(termWidget);

    connect(termWidget,&QTermWidget::customContextMenuRequested,this,&Terminal::onCustomContextMenuRequested);
    connect(termWidget,&QTermWidget::copyAvailable,this,&Terminal::copyToggle);
    connect(termWidget,&QTermWidget::finished,this,&Terminal::terminalClosed);

    //qDebug()<<termWidget->keyBindings();
}

void Terminal::toggleShow(bool s)
{
    if(s)
    {
        termWidget->startShellProgram();
    }
 }
