/*
 * Copyright (C) 2020  KylinSoft Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#ifndef KYLINBURNERABOUT_H
#define KYLINBURNERABOUT_H

#include <QWidget>

namespace Ui {
class KylinBurnerAbout;
}

class KylinBurnerAbout : public QWidget
{
    Q_OBJECT

public:
    explicit KylinBurnerAbout(QWidget *parent = nullptr);
    ~KylinBurnerAbout();
protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private slots:
    //void on_btnClose_clicked();

private:
    void labelCloseStyle(bool in);
private:
    Ui::KylinBurnerAbout *ui;
};

#endif // KYLINBURNERABOUT_H
