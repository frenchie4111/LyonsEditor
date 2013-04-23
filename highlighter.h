#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit Highlighter(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // HIGHLIGHTER_H
