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
        new_string = in.readAll();
    }
    return new_string;
}
