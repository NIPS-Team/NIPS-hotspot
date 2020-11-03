/*
    settingdialog.h

    This file is part of Hotspot, the Qt GUI for performance analysis.

    Copyright (C) 2020
    Author: Petr Lyapidevskiy <p.lyapidevskiy@nips.ru>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include "qwebstyleedit.h"
#include "mainwindow.h"
#include "parsers/perf/perfparser.h"
#include "resultspage.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    MainWindow* mainWindow;
    explicit SettingsDialog(QWidget* parent);
    ~SettingsDialog();
    void setTexts(QWebStyleEdit, const QString&, const QString&, const QString&);
    QString chooseDirectory();

signals:
    void sysrootChanged(const QString& path);

private:
    Ui::SettingsDialog *ui;
    void chooseDirectoryAndCopyToLineEdit(QWebStyleEdit* qWebStyleEdit);
    void chooseDirectoryAndAddToLineEdit(QWebStyleEdit* qWebStyleEdit);
    QString m_appPath;
    const QString infinityText = QLatin1String("INF");
    const QString infinityValue = QString::number(INT_MAX);
    bool maxStackChanged = false;

private slots:
    void on_btnSysroot_clicked();
    void on_btnApplicationPath_clicked();
    void on_btnTargetRoot_clicked();
    void on_btnExtraLibraryPaths_clicked();
    void on_btnDebugPaths_clicked();
    void on_btnKallsyms_clicked();
    void on_buttonBox_clicked(QAbstractButton* );
    void on_checkBoxOverrideWithPerfDataPath_clicked();
};

#endif // SETTINGSDIALOG_H
