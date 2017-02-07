#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QCheckBox>
#include<QPushButton>

class FindDialog : public QWidget
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = 0);

signals:
    void findDialogclosed();
    void findPrevSig();
    void findNxtSig(const QString &expr,bool re,bool cs,bool wo,bool wrap);
    void replaceSig(const QString &rep);
    void replaceAllSig();

public slots:
void emitFindDialogclose(bool b);
void emitFindNxt(bool b);
void emitFindPrev(bool b);
void emitReplace(bool b);
void emitReplaceAll(bool b);
private:
    QLabel *findLabel;
    QLabel *replaceLabel;
    QLineEdit *findText;
    QLineEdit *replaceText;
    QCheckBox *wholeWordFlag;
    QCheckBox *matchCaseFlag;
    QCheckBox *regExpFlag;
    QCheckBox *wrapFlag;
    QPushButton *findNxtBtn;
    QPushButton *findPrevBtn;
    QPushButton *replaceBtn;
    QPushButton *replaceAllBtn;
};

#endif // FINDDIALOG_H
