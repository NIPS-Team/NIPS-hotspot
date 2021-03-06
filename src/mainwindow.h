/*
  mainwindow.h

  This file is part of Hotspot, the Qt GUI for performance analysis.

  Copyright (C) 2016-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nate Rogers <nate.rogers@kdab.com>

  Licensees holding valid commercial KDAB Hotspot licenses may use this file in
  accordance with Hotspot Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <QMainWindow>
#include <QScopedPointer>
#include <QString>

#include <KSharedConfig>

namespace Ui {
class MainWindow;
}

class PerfParser;
class QStackedWidget;

class KRecentFilesAction;

class StartPage;
class ResultsPage;
class RecordPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QString getSysroot() const;
    QString getAppPath() const;
    QString getApplicationPath() const;
    QString getPerfDataPath() const;
    bool getOverrideAppPathWithPerfDataPath() const;
    QString getTargetRoot() const;
    QString getKallsyms() const;
    QString getDebugPaths() const;
    QString getExtraLibPaths() const;
    QString getArch() const;
    QString getMaxStack() const;

public slots:
    void setSysroot(const QString& path);
    void setKallsyms(const QString& path);
    void setDebugPaths(const QString& paths);
    void setExtraLibPaths(const QString& paths);
    void setAppPath(const QString& path);
    void setPerfDataPath(const QString& path);
    void setOverrideAppPathWithPerfDataPath(bool);
    void setTargetRoot(const QString& path);
    void setArch(const QString& arch);
    void setDisasmApproach(const QString& disasmApproach);
    void setVerbose(const QString& verbose);
    void setMaxStack(const QString& maxStack);
    void setBranchTraverse(const QString& branchTraverse);

    void clear();
    void openFile(const QString& path);
    void openFile(const QUrl& url);
    void reload();

    void onOpenFileButtonClicked();
    void onPathsAndArchSettingsButtonClicked();
    void onRecordButtonClicked();
    void onHomeButtonClicked();

    void aboutKDAB();
    void openSettingsDialog();
    void aboutHotspot();

    void setCodeNavigationIDE(QAction* action);
    void navigateToCode(const QString& url, int lineNumber, int columnNumber);

signals:
    void openFileError(const QString& errorMessage);
    void sysrootChanged(const QString& path);
    void kallsymsChanged(const QString& path);
    void debugPathsChanged(const QString& paths);
    void extraLibPathsChanged(const QString& paths);
    void appPathChanged(const QString& path);
    void archChanged(const QString& arch);

private:
    void closeEvent(QCloseEvent* event) override;
    void setupCodeNavigationMenu();
    void setupPathSettingsMenu();
    void setupFilterDisassemblyMenu();

    void setupViewMenu();

    QScopedPointer<Ui::MainWindow> ui;
    PerfParser* m_parser;
    KSharedConfigPtr m_config;
    QStackedWidget* m_pageStack;
    StartPage* m_startPage;
    RecordPage* m_recordPage;
    ResultsPage* m_resultsPage;

    QString m_sysroot;
    QString m_kallsyms;
    QString m_debugPaths;
    QString m_extraLibPaths;
    QString m_appPath;
    // Path to perf data file opened with File Open Dialog
    QString m_perfDataPath;
    // App Path will be overridden with perf data path
    bool m_overrideAppPathWithPerfDataPath;
    // Path to the copy of file system of the target machine
    QString m_targetRoot;
    // Architecture
    QString m_arch;
    // Disassembly approach code: 'symbol' - by function symbol, 'address' or default - by addresses range
    QString m_disasmApproach;
    // 'warning' - display warnings on the console, 'debug' - display debug information, 'all' - display both,
    // anything else - suppress warnings and debug information, except fatal and critical messages
    QString m_verbose;
    // Maximum callchain and branchStack size
    QString m_maxStack;
    // Short branchStack resolveCallchain traverse. Concerns lbr.
    QString m_branchTraverse;
    KRecentFilesAction* m_recentFilesAction = nullptr;
    QAction* m_reloadAction = nullptr;
};
