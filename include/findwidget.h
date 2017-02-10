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
#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QCheckBox>
#include<QPushButton>

class FindWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FindWidget(QWidget *parent = 0);

signals:
    void findWidgetclosed();
    void findPrevSig();
    void findNxtSig(const QString &expr,bool re,bool cs,bool wo,bool wrap);
    void replaceSig(const QString &rep);
    void replaceAllSig();

public slots:
void emitFindWidgetclose();
void emitFindNxt();
void emitFindPrev();
void emitReplace();
void emitReplaceAll();
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
