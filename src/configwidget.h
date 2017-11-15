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

#ifndef FCITXCONFIGPAGE_H
#define FCITXCONFIGPAGE_H

// Qt
#include <QWidget>

// KDE
#include <KColorButton>
#include <QDialog>
#include <QDialogButtonBox>

// Fcitx

class QCheckBox;
class QVBoxLayout;
class QStandardItemModel;

class QTabWidget;

namespace fcitx {

class DummyConfig;

class Global;

class SubConfigParser;

class ColorButton : public KColorButton {
    Q_OBJECT
public:
    explicit ColorButton(QWidget *parent = 0) : KColorButton(parent) {}
public slots:
    void setColor(const QColor &color) { KColorButton::setColor(color); }
};

class ConfigWidget : public QWidget {
    Q_OBJECT

    enum UIType { CW_Simple = 0x1, CW_Full = 0x2, CW_NoShow = 0x0 };

public:
    explicit ConfigWidget(struct _FcitxConfigFileDesc *cfdesc,
                          const QString &prefix, const QString &name,
                          const QString &subconfig = QString(),
                          const QString &addonName = QString(),
                          QWidget *parent = NULL);
    explicit ConfigWidget(FcitxAddon *addonEntry, QWidget *parent = 0);
    virtual ~ConfigWidget();

    static QDialog *configDialog(QWidget *parent, _FcitxConfigFileDesc *cfdesc,
                                 const QString &prefix, const QString &name,
                                 const QString &subconfig = QString(),
                                 const QString &addonName = QString());
    static QDialog *configDialog(QWidget *parent, FcitxAddon *addonEntry);

    DummyConfig *config() { return m_config; }

Q_SIGNALS:
    void changed();

public slots:
    void buttonClicked(QDialogButtonBox::StandardButton);
    void load();
private slots:
    void toggleSimpleFull();

private:
    QWidget *createFullConfigUi();
    QWidget *createSimpleConfigUi(bool skinAdvance);
    void setupConfigUi();
    void createConfigOptionWidget(FcitxConfigGroupDesc *cgdesc,
                                  FcitxConfigOptionDesc *codesc, QString &label,
                                  QString &tooltip, QWidget *&inputWidget,
                                  void *&newarg);
    void checkCanUseSimple();

    struct _FcitxConfigFileDesc *m_cfdesc;
    QString m_prefix;
    QString m_name;
    QString m_addonName;
    QVBoxLayout *m_switchLayout;
    QWidget *m_simpleWidget;
    QWidget *m_fullWidget;
    QCheckBox *m_advanceCheckBox;
    DummyConfig *m_config;
    SubConfigParser *m_parser;
    UIType m_simpleUiType;
    UIType m_fullUiType;
    QMap<QString, void *> m_argMap;
};
}

#endif
