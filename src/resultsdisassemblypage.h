#pragma once

#include <QWidget>
#include <QTemporaryFile>
#include <QStandardItemModel>
#include <QStack>
#include "data.h"
#include "models/searchdelegate.h"
#include "models/disassemblymodel.h"
#include <QItemSelection>

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

class ResultsDisassemblyPage : public QWidget
{
    static const int MSECS_PROCESS = 3600000;

    Q_OBJECT
    Q_ENUMS(Action)
public:
    enum Action {
        Disassembly,
        Annotate
    };

    explicit ResultsDisassemblyPage(FilterAndZoomStack* filterStack, PerfParser* parser,
                                 QWidget* parent = nullptr);
    ~ResultsDisassemblyPage();

    void clear();
    void clearTmpFiles();
    void filterDisassemblyBytes(bool filtered);
    void filterDisassemblyAddress(bool filtered);
    void switchOnIntelSyntax(bool intelSyntax);
    void switchDisassemblyMethod(bool disasmMethod);
    QByteArray processDisassemblyGenRun(QString processName);
    void setAsmViewModel(QStandardItemModel *model, int numTypes);
    void showDisassembly();
    void showDisassemblyBySymbol();
    void showDisassemblyByAddressRange();
    // Output Disassembly that is the result of running 'processName' command on tab Disassembly
    void showDisassembly(QString processName);
    void showAnnotate();
    void resetDisassembly();
    void setAppPath(const QString& path);
    void setData(const Data::Symbol& data);
    void setData(const Data::DisassemblyResult& data);
    void resetCallStack();
    void zoomFont(QWheelEvent *event);
    void wheelEvent(QWheelEvent *event);
    void getObjdumpVersion(QByteArray &processOutput);
    void searchTextAndHighlight();
    QByteArray processPerfAnnotateDiag(QString processName);
    Data::Symbol getCalleeSymbol(QString asmLine);
    void returnToCaller();
    void returnToJump();
    void setupDisassemblyContextMenu(QTreeView *view, int origFontSize);
    void setOpcodes(bool intelSyntax);
    void setAction(bool disasmMethod);
    void navigateToAddressInstruction(QModelIndex index, QString asmLine);
    void resizeEvent(QResizeEvent *event);
signals:
    void doubleClicked(QModelIndex);
public slots:
    void jumpToAsmCallee(QModelIndex);

private:
    FilterAndZoomStack* m_filterAndZoomStack;
    QScopedPointer<Ui::ResultsDisassemblyPage> ui;
    // Asm view model
    QStandardItemModel *model;
    // Call stack
    QStack<QMap<Data::Symbol, int>> m_callStack;
    // Perf.data path
    QString m_perfDataPath;
    // Current chosen function symbol
    Data::Symbol m_curSymbol;
    // Actual application path for current selected symbol
    QString m_curAppPath;
    // Annotate symfs option to look for files with symbols relative to this directory
    QString m_symfs;
    // List of symbol links in /tmp
    QStringList m_tmpAppList;
    // Application path
    QString m_appPath;
    // Target root
    QString m_targetRoot;
    // Extra libs path
    QString m_extraLibPaths;
    // Architecture
    QString m_arch;
    // Disassembly approach code: 'symbol' - by function symbol, 'address' or default - by addresses range
    QString m_disasmApproach;
    // Objdump binary name
    QString m_objdump;
    // Map of symbols and its locations with costs
    Data::DisassemblyResult m_disasmResult;
    // Disassembly action: Disassembly or Annotate
    Action m_action;
    // Not to show machine codes of Disassembly
    bool m_noShowRawInsn;
    // Not to show address of Disassembly
    bool m_noShowAddress;
    // Switch Assembly to Intel Syntax
    bool m_intelSyntaxDisassembly;
    // Default font size
    int m_origFontSize;
    // Version of objdump
    QString m_objdumpVersion;
    // Search delegate
    SearchDelegate *m_searchDelegate;
    // Map of Callees which can be Disassemblied
    QHash<int, Data::Symbol> m_callees;
    // Opcode of call
    QString opCodeCall;
    // Opcode of return
    QString opCodeReturn;
    // m_callees should be filled once for selected symbol
    bool m_calleesProcessed;
    // Jump instruction source
    QStack<QModelIndex> m_addressStack;
    // Setter for m_noShowRawInsn
    void setNoShowRawInsn(bool noShowRawInsn);
    // Setter for m_noShowAddress
    void setNoShowAddress(bool noShowAddress);
    // Setter for m_intelSyntaxDisassembly
    void setIntelSyntaxDisassembly(bool intelSyntax);
};
