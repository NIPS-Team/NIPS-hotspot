/*
  resultsbottomuppage.h

  This file is part of Hotspot, the Qt GUI for performance analysis.

  Copyright (C) 2017-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include <QWidget>
#include <QTemporaryFile>
#include "data.h"

class QMenu;

namespace Ui {
    class ResultsDisassemblyPage;
}

namespace Data {
    struct Symbol;
}

class QTreeView;

class PerfParser;
class FilterAndZoomStack;

class ResultsDisassemblyPage : public QWidget {
Q_OBJECT
    Q_ENUMS(Action)
public:
    enum Action {
        Disassembly,
        Annotate
    };

    explicit ResultsDisassemblyPage(FilterAndZoomStack *filterStack, PerfParser *parser,
                                    QWidget *parent = nullptr);
    ~ResultsDisassemblyPage();

    void clear();
    QByteArray processDisassemblyGenRun(QString processName);
    void showDisassembly();
    void showDisassemblyBySymbol();
    void showDisassemblyByAddressRange();
    // Output Disassembly that is the result of call process running 'processName' command on tab Disassembly
    void showDisassembly(QString processName);
    void showAnnotate();
    void setAppPath(const QString &path);
    void setData(const Data::Symbol &data);
    void setData(const Data::DisassemblyResult &data);

private:
    QScopedPointer<Ui::ResultsDisassemblyPage> ui;
    // Perf.data path
    QString m_perfDataPath;
    // Current chosen function symbol
    Data::Symbol m_curSymbol;
    // Application path
    QString m_appPath;
    // Extra libs path
    QString m_extraLibPaths;
    // Architecture
    QString m_arch;
    // Disassembly approach code: 'symbol' - by function symbol, 'address' or default - by addresses range
    QString m_disasmApproach;
    // Objdump binary name
    QString m_objdump;
    // Disassembly action: Disassembly or Annotate
    Action m_action;
};
