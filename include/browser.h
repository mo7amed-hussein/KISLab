#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include<QListWidget>
#include<QTreeWidget>

class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = 0);
    void addfile(QString name,QString desc);
    void showContextMenu(QTreeWidgetItem * item,const QPoint& gPos);

signals:
    void showFile(QString filePath);
    void closeFile(QString filePath);

public slots:

    void itemDClicked(QTreeWidgetItem * item, int column);
    void onCustomContextMenuRequested(const QPoint& pos);
    void showFileAction();
    void removefile();
   void openFolder();

private:
    QListWidget*fileList;
    QTreeWidget *filesTree;
    QTreeWidgetItem *filesRoot;
    QTreeWidgetItem *itemPopup;

};

#endif // BROWSER_H
