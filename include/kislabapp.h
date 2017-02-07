#ifndef KISLABAPP_H
#define KISLABAPP_H

#include <QObject>
#include<QDebug>
#include<QApplication>
#include <QEvent>
class KISLabApp : public QApplication
{
    Q_OBJECT
public:
     KISLabApp(int &argc, char *argv[]);

protected:

  virtual bool event(QEvent * event);
};

#endif // KISLABAPP_H
