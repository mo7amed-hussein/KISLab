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
#ifndef TERMINAL_H
#define TERMINAL_H

#include <QWidget>
#include<QGridLayout>
#include "qtermwidget.h"
class Terminal : public QWidget
{
    Q_OBJECT
public:
    explicit Terminal(QWidget *parent = 0);
    void configTerm();

signals:
    void closeTerminaldock();


public slots:
    void onCustomContextMenuRequested(const QPoint& pos);
    void copyToggle(bool c);
    void searchBarToggle();
    void paste();
    void copy();
    void terminalClosed();
    void toggleShow(bool s);

private:
    QTermWidget *termWidget;
    QAction *copyAction;
    QAction *pasteAction;
    QGridLayout *termLayout;
};

#endif // TERMINAL_H
