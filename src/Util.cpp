#include "Util.h"

#include <QUrl>
#include <QtGui>

#include <iostream>


QString Util::plainToRichText(QString text, QString fontFamily, int fontPointSize)
{
    // Use this to get the whole html shebaing, doctype and everything included
    QTextDocument doc;

    if (! fontFamily.isEmpty()){
        QFont font;
        font.setFamily(fontFamily);
        font.setPointSize(fontPointSize);
        doc.setDefaultFont(font);
    }

    doc.setPlainText(text);
    return doc.toHtml();
}

QString Util::richToPlainText(QString text)
{
    QTextDocument doc;
    doc.setHtml(text);
    return doc.toPlainText();
}

// todo!sv reimplement using QSyntaxHighlighter
QString Util::syntaxHighlight(QString richText)
{
    auto keywords = {"int", "float", "double", "long", "string", "char", "auto",
                     "std",
                     "return", "if", "then", "else", "while", "break", "include", "#pragma once"};

    for (const auto& keyword : keywords){
        QRegularExpression regexp(QString("\\b") + keyword + "\\b");
        richText.replace(regexp, QString("<span style=\"color:#45c6d6\">") + keyword + "</span>");
    }

    return richText;
}

void Util::writeFile(QString fileName, QString content)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)){
        return;
    }

    QTextStream out(&file);
    out << content;
    file.close();
}

QString Util::readFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        return "";
    }

    QTextStream in(&file);
    return in.readAll();
}

QString Util::urlToLocalFile(QString url)
{
    return QUrl(url).toLocalFile();
}

bool Util::isActive() const
{
    return m_isActive;
}

void Util::setActive(bool active)
{
    m_isActive = active;
    isActiveChanged();
}

Util::Util(const QCoreApplication &app)
    : m_settings(app.organizationName(), "pres.io")
{
}

QString Util::getLastUsedFile() const
{
    return m_settings.value("main/lastUsedFile").toString();
}

void Util::setLastUsedFile(QString value)
{
    m_settings.setValue("main/lastUsedFile", value);
}
