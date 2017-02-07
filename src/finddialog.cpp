#include "finddialog.h"
#include<QVBoxLayout>
#include<QLayout>
#include<QDebug>

FindDialog::FindDialog(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *findLayout=new QHBoxLayout;
    QHBoxLayout *flagsLayout=new QHBoxLayout;
    QHBoxLayout *replaceLayout=new QHBoxLayout;

    findLabel=new QLabel;
    findLabel->setText(tr("Find:"));
    findText=new QLineEdit;
    findText->setPlaceholderText("type to search");
    findText->setClearButtonEnabled(true);
    findNxtBtn=new QPushButton(tr("Find Next"));
    QPushButton *closeBtn=new QPushButton("X");
    closeBtn->setFixedSize(20,20);
    findPrevBtn=new QPushButton(tr("Find Previous"));

    findLayout->addWidget(findLabel);
    findLayout->addWidget(findText);
    findLayout->addWidget(findNxtBtn);
    findLayout->addWidget(findPrevBtn);
    findLayout->addStretch(0);
    findLayout->addWidget(closeBtn,Qt::AlignRight|Qt::AlignTop);


    replaceLabel=new QLabel(tr("Replace with:"));
    replaceText=new QLineEdit;

    replaceBtn=new QPushButton(tr("Replace"));
    replaceAllBtn=new QPushButton(tr("Replace All"));
    replaceLayout->addWidget(replaceLabel);
    replaceLayout->addWidget(replaceText);
    replaceLayout->addWidget(replaceBtn);
    replaceLayout->addWidget(replaceAllBtn);
    replaceLayout->addStretch(0);

    wholeWordFlag=new QCheckBox;
    wholeWordFlag->setText(tr("Match The Whole Word"));
    matchCaseFlag=new QCheckBox;
    matchCaseFlag->setText(tr("Match Case"));
    regExpFlag=new QCheckBox(tr("Regular Expression"));
    wrapFlag=new QCheckBox(tr("Wrap Text"));
    flagsLayout->addSpacing(50);
    flagsLayout->addWidget(wholeWordFlag);
    flagsLayout->addWidget(matchCaseFlag);
    flagsLayout->addWidget(regExpFlag);
    flagsLayout->addWidget(wrapFlag);
    flagsLayout->addStretch(0);
   connect(closeBtn,SIGNAL(clicked(bool)),this,SLOT(emitFindDialogclose(bool)));
   connect(findNxtBtn,SIGNAL(clicked(bool)),this,SLOT(emitFindNxt(bool)));
   connect(findPrevBtn,SIGNAL(clicked(bool)),this,SLOT(emitFindPrev(bool)));
   connect(replaceBtn,SIGNAL(clicked(bool)),this,SLOT(emitReplace(bool)));
   connect(replaceAllBtn,SIGNAL(clicked(bool)),this,SLOT(emitReplaceAll(bool)));

   mainLayout->addLayout(findLayout);
   mainLayout->addLayout(flagsLayout);
   mainLayout->addLayout(replaceLayout);
}

void FindDialog::emitFindDialogclose(bool b)
{
    qDebug()<<"";
    emit findDialogclosed();
}
void FindDialog::emitFindNxt(bool b)
{
    qDebug()<<"find next";
    if(!findText->text().isEmpty())
    {
    emit findNxtSig(findText->text(),regExpFlag->isChecked(),matchCaseFlag->isChecked(),wholeWordFlag->isChecked(),wrapFlag->isChecked());
    }
}

void FindDialog::emitFindPrev(bool b)
{
    qDebug()<<"find prev";
    emit findPrevSig();
}

void FindDialog::emitReplace(bool b)
{
    qDebug()<<"replace";
    if(!replaceText->text().isEmpty())
    {
     emit replaceSig(replaceText->text());
    }
}

void FindDialog::emitReplaceAll(bool b)
{
    qDebug()<<"replace all";
    emit replaceAllSig();
}
