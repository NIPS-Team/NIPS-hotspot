/*
    disassemblymodel.h

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

#pragma once

#include <QStandardItemModel>

enum Roles {
    SortRole = Qt::UserRole,
    TotalCostRole
};

class DisassemblyModel : public QStandardItemModel {
Q_OBJECT
public:
    ~DisassemblyModel();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
};
