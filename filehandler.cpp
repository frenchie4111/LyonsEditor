#include <QTextStream>
#include <string>
#include <QFile>
#include <iostream>
#include <QMessageBox>

#include "filehandler.h"

void write_to_file(QString file, QString write) {
    QFile data(file);
    if( data.open(QFile::WriteOnly) ) {
        QTextStream out(&data);
        out << write;
        if( write.at( write.length() - 1 ) != '\n' ) {
            out << endl;
        }
    }
}

QString read_from_file(QString file) {
    QString new_string = "";
    QFile data(file);
    if( data.open(QFile::ReadOnly) ) {
        QTextStream in(&data);
        while( !in.atEnd() ) {
            QString line = in.readLine();

            line = convert_to_html(line);

            new_string.append(convert_to_html( line ) + "<br/>");
        }
    }
    return new_string;
}

QString convert_to_html(QString text) {
    QString new_string = text;

    new_string = new_string.replace(QRegExp("\\t"),QString("&nbsp;&nbsp;&nbsp;&nbsp;"));
    new_string = new_string.replace(QRegExp("\\s"),QString("&nbsp;"));

    return new_string;
}
