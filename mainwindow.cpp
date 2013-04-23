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

    setWindowTitle("SS Text Editor");

    ui_textEdit = qFindChild<QTextEdit*>(this, "mainEdit");
    ui_textEdit->setText("Press Ctrl+O to open a file");

    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);
    ui_textEdit->setFont(font);

    const int tabStop = 4;  // 4 characters

    QFontMetrics metrics(font);
    ui_textEdit->setTabStopWidth(tabStop * metrics.width(' '));

    connect(ui_textEdit, SIGNAL(textChanged()), this, SLOT( textChanged()) );
    connect( this, SIGNAL(destroyed()), this, SLOT(savedialog_and_close()));

    textEdited = false;

    set_keybindings();
}

void MainWindow::closeEvent( QCloseEvent *event ) {
    savedialog_and_close();
}

void MainWindow::load_text(QString file) {

    if( !openFileName.isEmpty() ) {
        openFiles.insert( openFileName, ui_textEdit->toPlainText() );
        openFileQueue.push_front(openFileName);
    }

    openFileName = file;

    QString fileText = read_from_file(openFileName);
    openFiles.insert(openFileName, fileText);

    ui_textEdit->setText( fileText );

    setWindowTitle(openFileName);

    textEdited = false;
}

void MainWindow::load_text() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));
    load_text( fileName );
}

void MainWindow::load_another() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));
    load_text( fileName );
}

void MainWindow::save_text() {
    QString text = ui_textEdit->toPlainText();
    write_to_file(openFileName, text);
    textEdited = false;
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
              break;
          case QMessageBox::Discard:
              break;
          case QMessageBox::Cancel:
          default:
              break;
        }
    } else {
    }
}

void MainWindow::maximize_window() {
    if( isMaximized ) {
        showNormal();
        isMaximized = !isMaximized;
    } else {
        showMaximized();
        isMaximized = !isMaximized;
    }
 }

void MainWindow::switch_window() {
    if( openFiles.keys().size() > 1 ) {
        QString new_file = openFileQueue.front();
        openFileQueue.pop_front();

        openFileQueue.push_back( openFileName );

        openFileName = new_file;
        ui_textEdit->setText( openFiles.value( openFileName ) );
    } else {
        // NO OP
    }
}

void MainWindow::set_keybindings() {
    QShortcut *closeShortcut = new QShortcut(QKeySequence("Ctrl+W"), this);
    closeShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(closeShortcut, SIGNAL(activated()), this, SLOT(close()));

    QShortcut *openShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    openShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(openShortcut, SIGNAL(activated()), this, SLOT(load_text()));

    QShortcut *openAnotherShortcut = new QShortcut(QKeySequence("Ctrl+Shift+O"), this);
    openAnotherShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(openAnotherShortcut, SIGNAL(activated()), this, SLOT(load_text()));

    QShortcut *saveShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
    saveShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(saveShortcut, SIGNAL(activated()), this, SLOT(save_text()));

    QShortcut *switchShortcut = new QShortcut(QKeySequence("Ctrl+Tab"), this);
    switchShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(switchShortcut, SIGNAL(activated()), this, SLOT(switch_window()));

    QShortcut *maximizeShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    maximizeShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(maximizeShortcut, SIGNAL(activated()), this, SLOT(maximize_window()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
