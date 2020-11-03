/*
    searchdelegate.cpp

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

#include "searchdelegate.h"
#include "costdelegate.h"
#include "disassemblymodel.h"

#include <QDebug>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QStyledItemDelegate>

#include <cmath>

SearchDelegate::SearchDelegate(QObject *parent)
        : QStyledItemDelegate(parent) {
    costDelegate = new CostDelegate(SortRole, TotalCostRole, parent);
}

SearchDelegate::~SearchDelegate() = default;

/**
 *  Overriden paint
 * @param painter
 * @param option
 * @param index
 */
void SearchDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid())
        return;

    if (index.column() == 0) {
        QString text = index.model()->data(index, Qt::DisplayRole).toString();
        QTextDocument *document = new QTextDocument(text);

        if (option.state & QStyle::State_Selected) {
            painter->setPen(Qt::white);
            painter->fillRect(option.rect, option.palette.highlight());
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }
        Highlighter *highlighter = new Highlighter(document);
        highlighter->setSearchText(m_searchText);
        highlighter->setArch(m_arch);
        highlighter->setCallee(m_callees.contains(index.row()));
        highlighter->setDiagnosticStyle(m_diagnosticStyle);
        highlighter->setHighlightColor(option.palette.highlight());

        highlighter->rehighlight();

        painter->save();
        document->setDefaultFont(painter->font());
        painter->setClipRect(option.rect.x(), option.rect.y(), option.rect.width(), option.rect.height());

        int offset_y = (option.rect.height() - document->size().height()) / 2;
        painter->translate(option.rect.x(), option.rect.y() + offset_y);
        document->drawContents(painter);
        painter->restore();
        delete document;
    } else {
        costDelegate->paint(painter, option, index);
    }
}
