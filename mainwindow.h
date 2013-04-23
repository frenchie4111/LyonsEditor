#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextEdit>
#include <QMainWindow>
#include <QString>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     void load_text(QString file);
     void closeEvent( QCloseEvent *event );

public slots:
    void load_text();
    void load_another();
    void save_text();
    void savedialog_and_close();
    void maximize_window();
    void textChanged() { textEdited = true; }
    void switch_window();
    
private:
    Ui::MainWindow *ui;
    QTextEdit *ui_textEdit;
    QMap<QString, QString> openFiles;
    QList<QString> openFileQueue;
    QString openFileName;
    bool textEdited, isMaximized;
    void set_keybindings();
};

#endif // MAINWINDOW_H
