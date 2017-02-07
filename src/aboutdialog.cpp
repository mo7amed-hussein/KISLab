#include "aboutdialog.h"
#include<QLabel>
#include<QPixmap>
#include<QVBoxLayout>
#include<QTabWidget>
#include<QPalette>
AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QLabel *splash=new QLabel(this);
    QImage img(":/images/icons/kis.jpg");
    splash->setPixmap(QPixmap::fromImage(img));
    splash->setScaledContents(true);
    splash->setFixedSize(img.size());

    this->setWindowFlags(Qt::Tool);
    this->setWindowTitle(tr("About KISLab"));

    QLabel *developer=new QLabel(this);
    developer->setText(tr("<b>KISLab</b> was developed by"
                          "<p> Mohamed Hussein"
                          "<p> Feb,2017"));
    developer->setAlignment(Qt::AlignCenter);
    QLabel *developerContact=new QLabel(this);
    developerContact->setText(tr("<br>for contribution or bugs "
                                 "<p>please contact us"
                                 "<p><a href=\"mailto:m.hussein1389@gmail.com\">m.hussein1389@gmail.com</a>"
                                 "<p><a href=\"https://github.com/mo7amed-hussein/KISLab\">Github</a><br>"));

    developerContact->setOpenExternalLinks(true);

    developerContact->setAlignment(Qt::AlignCenter);
    QLabel *license=new QLabel(this);
    license->setText(tr("<b>KISLab</b> was distributed "
                        "under the terms of<p> GNU public license (GPL)"));

    license->setAlignment(Qt::AlignCenter);
    QLabel *credits=new QLabel(this);
    credits->setText(tr("<br><p>Qt"
                        "<p>QsciScintilla"
                        "<p>QTermWidget<br>"));
    credits->setAlignment(Qt::AlignCenter);

    QTabWidget *aboutTabs=new QTabWidget;
    aboutTabs->addTab(developer,"Developer");
    aboutTabs->addTab(license,"License");
    aboutTabs->addTab(developerContact,"Contact");
    aboutTabs->addTab(credits,"Credits");
    aboutTabs->setContentsMargins(10,20,10,20);

    mainLayout->setAlignment(Qt::AlignVCenter);

    mainLayout->addWidget(splash,0,Qt::AlignCenter);
    mainLayout->addWidget(aboutTabs,0,Qt::AlignCenter);


}
