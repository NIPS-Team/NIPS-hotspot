/*
    highlighter.h

    This file is part of Hotspot, the Qt GUI for performance analysis.

    Copyright (C) 2020
    Author: Darya Knysh <d.knysh@nips.ru>

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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;

QT_END_NAMESPACE

class Highlighter : public QSyntaxHighlighter {
Q_OBJECT

public:
    Highlighter(QTextDocument *parent = nullptr);

    void setArch(QString arch) {
        m_arch = arch;
    }

    QString getArch() {
        return m_arch;
    }

    void setSearchText(QString searchText) {
        m_searchText = searchText;
    }

    QString getSearchText() {
        return m_searchText;
    }

    void setHighlightColor(QBrush highlightColor) {
        m_highlightColor = highlightColor;
    }

    QBrush getHighlightColor() {
        return m_highlightColor;
    }

    void setDiagnosticStyle(bool diagnosticStyle) {
        m_diagnosticStyle = diagnosticStyle;
    }

    bool getDiagnosticStyle() {
        return m_diagnosticStyle;
    }

    bool getCallee() {
        return m_callee;
    }

    void setCallee(bool callee) {
        m_callee = callee;
    }

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> regHighlightingRules;    
    QVector<HighlightingRule> callHighlightingRules;
    QVector<HighlightingRule> offsetHighlightingRules;

    QVector<HighlightingRule> searchHighlightingRules;
    QVector<HighlightingRule> commentHighlightingRules;

    QTextCharFormat registersFormat;
    QTextCharFormat offsetFormat;
    QTextCharFormat callFormat;
    QTextCharFormat searchFormat;
    QTextCharFormat commentFormat;

    QString m_arch;
    QString m_searchText;
    QBrush m_highlightColor;
    bool m_diagnosticStyle;
    bool m_callee;
};

#endif
