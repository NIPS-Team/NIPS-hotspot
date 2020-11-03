/*
    qwebstyleedit.cpp

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

#include "qwebstyleedit.h"
#include <QPalette>
#include <QKeyEvent>

// Widget inherited from LineEdit that was updated with grayed text functionality
QWebStyleEdit::QWebStyleEdit(QWidget * parent,QString grText):QLineEdit(parent)
{
    // When the control is created the modified flag is set to false
    modified = false;
    // Set initial grayed text from constructor parameters
    setGrayedText(grText);
    // Set text style: one style if text was modified, and another if not
    setColors();
}

// Setter for grayed text property
void QWebStyleEdit::setGrayedText(const QString &grText)
{
    if (m_grText.isEmpty())
        m_grText = grText;
    // Set the value of text edit control
    setText(QLatin1String(""));
}

// Getter for grayed text property
QString QWebStyleEdit::grayedText() const {
    return m_grText;
}

// Checking cases when the control is considered modified
void QWebStyleEdit::keyPressEvent(QKeyEvent* e) {
    if (!modified) {
        // Start typing first letter in an empty line edit
        QLineEdit::setText(QLatin1String(""));
        modified = true;
    }
    // Pass key value to standard LineEdit control
    QLineEdit::keyPressEvent(e);
    // When, after pressing the key, text became:
    // empty - set modified flag to false
    if (text().isEmpty())
        modified = false;
    // not empty - set true
    else
        modified = true;
    // Update text style
    setColors();
}

void QWebStyleEdit::setBackgroundColor(QColor color) {
    QPalette p = palette();
    p.setColor(QPalette::Base, color);
    setPalette(p);
}

void QWebStyleEdit::setForegroundColor(QColor color) {
    QPalette p = palette();
    p.setColor(QPalette::Text, color);
    setPalette(p);
}

void QWebStyleEdit::setText(const QString& text)
{
    // Call standard LineEdit method to set the text
    QLineEdit::setText(text);
    // Check if the text became empty and set modified flag
    if (text.isEmpty())
        modified = false;
    else
        modified = true;
    // Update text style
    setColors();
}

QString QWebStyleEdit::text() const {
    // If text was modified return text from standard LineEdit control
    if (modified)
        return QLineEdit::text();
    // Else return an empty string
    return QLatin1String("");
}

void QWebStyleEdit::setItalic(bool it)
{
    QFont fnt(font());
    fnt.setItalic(it);
    setFont(fnt);
}

// Update the text style in LineEdit control
void QWebStyleEdit::setColors() {
    if (modified) {
        setBackgroundColor(textBGColor);
        setForegroundColor(textFGColor);
        setItalic(false);
    } else {
        setBackgroundColor(grTextBGColor);
        setForegroundColor(grTextFGColor);
        setItalic(true);
        QLineEdit::setText(m_grText);
    }
}

void QWebStyleEdit::setTextEnabled() {
    setEnabled(true);
    setForegroundColor(textFGColor);
}

void QWebStyleEdit::setTextDisabled() {
    setDisabled(true);
    setForegroundColor(grTextFGColor);
}
