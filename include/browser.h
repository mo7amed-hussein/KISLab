#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include<QListWidget>

class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = 0);

signals:

public slots:
private:
    QListWidget*fileList;
};

#endif // BROWSER_H
