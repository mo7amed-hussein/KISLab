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
    void searchBarToggle(bool c);
    void paste();
    void copy();
    void getFocus();
    void terminalClosed();
    void toggleShow(bool s);
private:
    QTermWidget *termWidget;
    QAction *copyAction;
    QAction *pasteAction;
    QGridLayout *termLayout;
};

#endif // TERMINAL_H
