/*
    disassemblymodel.cpp

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

#include "disassemblymodel.h"
#include "qglobal.h"

#include <QDebug>

DisassemblyModel::~DisassemblyModel() = default;

/**
 *  Override method data of QStandardItemModel to colorize Disassembly instructions events costs
 * @param index
 * @param role
 * @return
 */
QVariant DisassemblyModel::data(const QModelIndex &index, int role) const {
    if (index.column() > 0) {
        if (role == SortRole) {
            QVariant variant = QStandardItemModel::data(index);
            QString dataString = variant.toString().replace(QLatin1String("%"), QLatin1String(""));
            return qRound(dataString.toDouble());
        } else if (role == TotalCostRole) {
            return 100;
        }
    }
    return QStandardItemModel::data(index, role);
}