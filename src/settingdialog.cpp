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
#include "settingdialog.h"
#include<QPushButton>
#include<QLabel>
#include<QSizePolicy>
#include<QSettings>
#include<QDebug>
SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *autoSaveLayout=new QHBoxLayout;
    QHBoxLayout *btnsLayout=new QHBoxLayout;
    QHBoxLayout *fontLayout=new QHBoxLayout;


    this->setWindowFlags(Qt::Tool);
    this->setWindowTitle(tr("Settings"));

    autosave=new QCheckBox;
    autosave->setText(tr("AutoSave Files every"));

    autosavetime=new QSpinBox;
    autosavetime->setMinimum(1);
    autosavetime->setValue(4);
    autosavetime->setMaximum(60);
    autosavetime->setEnabled(false);

    connect(autosave,&QCheckBox::toggled,autosavetime,&QSpinBox::setEnabled);

    QLabel *timeLabel=new QLabel(tr("Minutes"));

    fontSize=new QSpinBox;

    autoSaveLayout->addWidget(autosave);
    autoSaveLayout->addWidget(autosavetime);
    autoSaveLayout->addWidget(timeLabel);

    QPushButton *cancel=new QPushButton(tr("Cancel"));
    QPushButton *save=new QPushButton(tr("Save"));

    connect(cancel,&QPushButton::clicked,this,&SettingDialog::close);
    connect(save,&QPushButton::clicked,this,&SettingDialog::save);


    btnsLayout->addWidget(cancel);
    btnsLayout->addWidget(save);
    QLabel *fontLabel=new QLabel(tr("Font:"));
     QLabel *fontSizeLabel=new QLabel(tr("Font Size:"));
    font=new QFontComboBox;
    font->setFontFilters(QFontComboBox::ScalableFonts);
    fontLayout->addWidget(fontLabel);
    fontLayout->addWidget(font);
    fontLayout->addWidget(fontSizeLabel);
    fontLayout->addWidget(fontSize);

    mainLayout->addLayout(autoSaveLayout);
    mainLayout->addLayout(fontLayout);
    mainLayout->addLayout(btnsLayout);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    readSetting();

}
void SettingDialog::readSetting()
{
    QSettings set;
    QFont f;
    QString fStr=set.value("FONT",f.defaultFamily()).toString();
    f.setFamily(fStr);
    int fontsize=set.value("FONT_SIZE",14).toInt();
    bool saveFlag=set.value("AUTOSAVE",false).toBool();
    int saveTime=set.value("SAVE_TIME",5).toInt();
   // qDebug()<<"done here 1";
    autosave->setChecked(saveFlag);
    // qDebug()<<"done here 3";
    autosavetime->setValue(saveTime);
    //qDebug()<<"done here 2";
    font->setCurrentFont(f);
    fontSize->setValue(fontsize);

}

void SettingDialog::writeSetting()
{
    QSettings set;
    QFont f=font->currentFont();
    QString fStr=f.family();

    int fontsize=fontSize->value();
    bool saveFlag=autosave->isChecked();
    int saveTime=autosavetime->value();
    set.setValue("FONT",fStr);
    set.setValue("FONT_SIZE",fontsize);
    set.setValue("AUTOSAVE",saveFlag);
    set.setValue("SAVE_TIME",saveTime);
}
 void SettingDialog::save()
 {
     writeSetting();
     //this->close();
     this->done(1);
 }

