/***************************************************************************
 *   Copyright (C) 2011~2011 by CSSlayer                                   *
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
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef IM_CONFIG_DIALOG_H
#define IM_CONFIG_DIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

class KeyboardLayoutWidget;
class QComboBox;
namespace fcitx {

class ConfigWidget;
class IMConfigDialog : public QDialog {
    Q_OBJECT
public:
    explicit IMConfigDialog(const QString &imName, QWidget *parent = 0);

private slots:
    void onButtonClicked(QDialogButtonBox::StandardButton code);
    void layoutComboBoxChanged();

private:
    QString m_imName;
    QComboBox *m_layoutCombobox;
    KeyboardLayoutWidget *m_layoutWidget;
};
}

#endif
