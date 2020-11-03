/*
    qwebstyleedit.h

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

#ifndef QWEBSTYLEEDIT_H
#define QWEBSTYLEEDIT_H

#include <QLineEdit>
#include <QColor>

class QWebStyleEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString grayedText READ grayedText WRITE setGrayedText)

    QString m_text;
    QString m_grText;
    const QColor textBGColor = palette().color(QPalette::Base);
    const QColor grTextBGColor = palette().color(QPalette::Base);
    const QColor textFGColor = palette().color(QPalette::Text);
    const QColor grTextFGColor = palette().color(QPalette::Midlight);

    bool modified;

    void setBackgroundColor(QColor);
    void setForegroundColor(QColor);
    void setItalic(bool);

public:
    QWebStyleEdit(QWidget* parent = 0, QString grText = QString());

    void setText(const QString&);
    QString text() const;
    void setGrayedText(const QString&);
    QString grayedText() const;

    void grTextFGColorsetText(const QString&);
    void setColors();
    void setTextEnabled();
    void setTextDisabled();
protected:
    void keyPressEvent(QKeyEvent*) override;
};

#endif // QWEBSTYLEEDIT_H
