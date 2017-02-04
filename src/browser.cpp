#include "browser.h"

Browser::Browser(QWidget *parent) : QWidget(parent)
{
    fileList=new QListWidget(this);
    fileList->addItem("mm");

}
