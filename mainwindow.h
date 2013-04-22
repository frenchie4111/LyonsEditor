#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextEdit>
#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void load_text();
    void save_text();
    void savedialog_and_close();
    
private:
    Ui::MainWindow *ui;
    QTextEdit *ui_textEdit;
    QString openfile;
    bool textEdited;
    void set_keybindings();
};

#endif // MAINWINDOW_H
