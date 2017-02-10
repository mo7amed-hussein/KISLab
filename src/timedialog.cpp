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
#include "timedialog.h"
#include<QLabel>
#include<QPushButton>
#include<QDate>
#include<QTime>
#include<QDebug>

TimeDialog::TimeDialog(QWidget *parent) : QDialog(parent)
{

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *btnLayout=new QHBoxLayout;

    this->setWindowFlags(Qt::Tool);

    QLabel *selectLabel=new QLabel;
    selectLabel->setText(tr("Select Format :"));

    formats=new QListWidget;

    QPushButton *cancelBtn=new QPushButton(tr("Cancel"));
    QPushButton *insertBtn=new QPushButton(tr("Insert"));
    connect(insertBtn,&QPushButton::clicked,this,&TimeDialog::insert);
    connect(cancelBtn,&QPushButton::clicked,this,&TimeDialog::close);

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(insertBtn);

    mainLayout->addWidget(selectLabel);
    mainLayout->addWidget(formats);
    mainLayout->addLayout(btnLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    QDate d(QDate::currentDate());
    QTime t(QTime::currentTime());

    formats->addItem(d.toString(Qt::TextDate));
    formats->addItem(d.toString(Qt::ISODate));
    formats->addItem(d.toString(Qt::SystemLocaleShortDate));
    formats->addItem(d.toString(Qt::SystemLocaleLongDate));
    formats->addItem(t.toString(Qt::ISODate));
    formats->addItem(t.toString(Qt::SystemLocaleShortDate));
    formats->addItem(t.toString(Qt::SystemLocaleLongDate));
}

void TimeDialog::insert()
{
    format=formats->selectedItems()[0]->text();
   // qDebug()<<format;
    this->close();
}

QString TimeDialog::getFormat()
{
    this->exec();
    return format;
}
