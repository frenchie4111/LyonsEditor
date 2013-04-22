#include <QTextEdit>
#include <QShortcut>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filehandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //showMaximized();

    setWindowTitle("SS Text Editor");

    ui_textEdit = qFindChild<QTextEdit*>(this, "mainEdit");
    ui_textEdit->setHtml("Press Ctrl+O to open a file");

    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);
    ui_textEdit->setFont(font);

    const int tabStop = 4;  // 4 characters

    QFontMetrics metrics(font);
    ui_textEdit->setTabStopWidth(tabStop * metrics.width(' '));

    set_keybindings();
}

void MainWindow::load_text() {
    openfile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));
    ui_textEdit->setText(read_from_file( openfile ) );
    setWindowTitle(openfile);
    textEdited = false;
}

void MainWindow::save_text() {
    QString text = ui_textEdit->toPlainText();
    write_to_file(openfile, text);
}

void MainWindow::savedialog_and_close() {
    if( textEdited ) {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              save_text();
              close();
              break;
          case QMessageBox::Discard:
                close();
              break;
          case QMessageBox::Cancel:
          default:
              break;
        }
    } else {
        close();
    }
}

void MainWindow::set_keybindings() {
    QShortcut *closeShortcut = new QShortcut(QKeySequence("Ctrl+W"), this);
    closeShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(closeShortcut, SIGNAL(activated()), this, SLOT(savedialog_and_close()));

    QShortcut *openShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    openShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(openShortcut, SIGNAL(activated()), this, SLOT(load_text()));

    QShortcut *saveShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
    saveShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(saveShortcut, SIGNAL(activated()), this, SLOT(save_text()));

    QShortcut *maximizeShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    maximizeShortcut->setContext(Qt::ApplicationShortcut);
}

MainWindow::~MainWindow()
{
    delete ui;
}
