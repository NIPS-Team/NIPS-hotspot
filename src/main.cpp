/*
  main.cpp

  This file is part of Hotspot, the Qt GUI for performance analysis.

  Copyright (C) 2016-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Milian Wolff <milian.wolff@kdab.com>

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

#include <QApplication>
#include <QCommandLineParser>
#include <QProcessEnvironment>
#include <QFile>

#include "hotspot-config.h"
#include "mainwindow.h"
#include "models/data.h"
#include "util.h"

#include <ThreadWeaver/ThreadWeaver>
#include <QThread>

int main(int argc, char** argv)
{
    QCoreApplication::setOrganizationName(QStringLiteral("KDAB"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("kdab.com"));
    QCoreApplication::setApplicationName(QStringLiteral("hotspot"));
    QCoreApplication::setApplicationVersion(QStringLiteral(HOTSPOT_VERSION_STRING));

    QApplication app(argc, argv);

    // init
    Util::appImageEnvironment();

#if APPIMAGE_BUILD

    // cleanup the environment when we are running from within the AppImage
    // to allow launching system applications using Qt without them loading
    // the bundled Qt we ship in the AppImage
    auto LD_LIBRARY_PATH = qgetenv("LD_LIBRARY_PATH");
    LD_LIBRARY_PATH.remove(0, LD_LIBRARY_PATH.indexOf(':') + 1);
    qputenv("LD_LIBRARY_PATH", LD_LIBRARY_PATH);
#endif

    app.setWindowIcon(QIcon(QStringLiteral(":/images/icons/512-hotspot_app_icon.png")));
    qRegisterMetaType<Data::DisassemblyResult>();
    qRegisterMetaType<Data::Summary>();
    qRegisterMetaType<Data::BottomUp>();
    qRegisterMetaType<Data::TopDown>();
    qRegisterMetaType<Data::CallerCalleeEntryMap>("Data::CallerCalleeEntryMap");
    qRegisterMetaType<Data::BottomUpResults>();
    qRegisterMetaType<Data::TopDownResults>();
    qRegisterMetaType<Data::CallerCalleeResults>();
    qRegisterMetaType<Data::EventResults>();

#if APPIMAGE_BUILD
    QIcon::setThemeSearchPaths({app.applicationDirPath() + QLatin1String("/../share/icons/")});
    QIcon::setThemeName(QStringLiteral("breeze"));
#endif

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Linux perf GUI for performance analysis."));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption sysroot(QLatin1String("sysroot"),
                               QCoreApplication::translate("main", "Path to sysroot which is used to find libraries."),
                               QLatin1String("path"));
    parser.addOption(sysroot);

    QCommandLineOption kallsyms(
        QLatin1String("kallsyms"),
        QCoreApplication::translate("main", "Path to kallsyms file which is used to resolve kernel symbols."),
        QLatin1String("path"));
    parser.addOption(kallsyms);

    QCommandLineOption debugPaths(
        QLatin1String("debugPaths"),
        QCoreApplication::translate("main", "Colon separated list of paths that contain debug information."),
        QLatin1String("paths"));
    parser.addOption(debugPaths);

    QCommandLineOption extraLibPaths(
        QLatin1String("extraLibPaths"),
        QCoreApplication::translate("main", "Colon separated list of extra paths to find libraries."),
        QLatin1String("paths"));
    parser.addOption(extraLibPaths);

    QCommandLineOption appPath(
        QLatin1String("appPath"),
        QCoreApplication::translate("main", "Path to folder containing the application executable and libraries."),
        QLatin1String("path"));
    parser.addOption(appPath);

    QCommandLineOption targetRoot(
        QLatin1String("targetRoot"),
        QCoreApplication::translate("main", "Path to copy of target file system structure."),
        QLatin1String("path"));
    parser.addOption(targetRoot);

    QCommandLineOption arch(QLatin1String("arch"),
                            QCoreApplication::translate("main", "Architecture to use for unwinding."),
                            QLatin1String("path"));
    parser.addOption(arch);

    QCommandLineOption disasmApproach(QLatin1String("disasm-approach"),
                            QCoreApplication::translate("main", "Objdump way to generate Disassembly - by symbol or by addresses."),
                            QLatin1String("disasmApproach"));
    parser.addOption(disasmApproach);

    QCommandLineOption verbose(QLatin1String("verbose"),
                               QCoreApplication::translate("main",
                                                           "Set the value to 'warning'- to display warnings on the console."
                                                           " Set the value to 'debug' - to display debugging information on the console."
                                                           " Set the value to 'all' - to display warnings and debugging information on the console."
                                                           " By default, all warnings and debugging information are suppressed."),
                               QLatin1String("verbose"));
    parser.addOption(verbose);

    QCommandLineOption maxStack(QLatin1String("max-stack"),
                                QCoreApplication::translate("main", "Maximum callchain and branchStack sizes."),
                                QLatin1String("max-stack"));
    parser.addOption(maxStack);


    QCommandLineOption branchTraverse(QLatin1String("branch-traverse"),
                                      QCoreApplication::translate("main",
                                      "Short branchStack resolveCallchain traverse. Concerns lbr."));
    parser.addOption(branchTraverse);

    parser.addPositionalArgument(
        QStringLiteral("files"),
        QCoreApplication::translate("main", "Optional input files to open on startup, i.e. perf.data files."),
        QStringLiteral("[files...]"));

    parser.process(app);

    ThreadWeaver::Queue::instance()->setMaximumNumberOfThreads(QThread::idealThreadCount());

    auto applyCliArgs = [&](MainWindow* window) {
        if (parser.isSet(sysroot)) {
            window->setSysroot(parser.value(sysroot));
        }
        if (parser.isSet(kallsyms)) {
            window->setKallsyms(parser.value(kallsyms));
        }
        if (parser.isSet(debugPaths)) {
            window->setDebugPaths(parser.value(debugPaths));
        }
        if (parser.isSet(extraLibPaths)) {
            window->setExtraLibPaths(parser.value(extraLibPaths));
        }
        if (parser.isSet(appPath)) {
            window->setAppPath(parser.value(appPath));
        }
        if (parser.isSet(targetRoot)) {
            window->setTargetRoot(parser.value(targetRoot));
        }
        if (parser.isSet(arch)) {
            window->setArch(parser.value(arch));
        }
        if (parser.isSet(disasmApproach)) {
            window->setDisasmApproach(parser.value(disasmApproach));
        }
        if (parser.isSet(verbose)) {
            window->setVerbose(parser.value(verbose));
        }
        if (parser.isSet(maxStack)) {
            window->setMaxStack(parser.value(maxStack));
        }
        if (parser.isSet(branchTraverse)) {
            window->setBranchTraverse(branchTraverse.names().at(0));
        }
    };

    for (const auto& file : parser.positionalArguments()) {
        auto window = new MainWindow;
        applyCliArgs(window);
        window->openFile(file);
        window->show();
    }

    // show at least one mainwindow
    if (parser.positionalArguments().isEmpty()) {
        auto window = new MainWindow;
        applyCliArgs(window);

        // open perf.data in current CWD, if it exists
        // this brings hotspot closer to the behavior of "perf report"
        const auto perfDataFile = QStringLiteral("perf.data");
        if (QFile::exists(perfDataFile)) {
            window->openFile(perfDataFile);
        }

        window->show();
    }

    return app.exec();
}
