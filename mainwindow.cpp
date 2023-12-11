#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered,this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered,this, &MainWindow::saveFile);
    connect(ui->actionSaveAs, &QAction::triggered,this, &MainWindow::saveFileAs);

    connect(ui->actionOpenRight, &QAction::triggered,this, &MainWindow::openFile);
    connect(ui->actionSaveRight, &QAction::triggered,this, &MainWindow::saveFile);
    connect(ui->actionSaveAsRight, &QAction::triggered,this, &MainWindow::saveFileAs);

    //newFile();
    isSaved = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(QPlainTextEdit *editor)
{
    ui->editor->clear();
    filename.clear();
    isSaved = false;
    ui->statusbar->showMessage("New File");
}

void MainWindow::openFile(QPlainTextEdit *editor)
{
    QString temp = QFileDialog::getOpenFileName(this,"Open File",QString(),"Text Files (*txt);;All Files (*,*)");

    if(temp.isEmpty()) return;

    filename = temp;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        newFile();
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->editor->setPlainText(stream.readAll());
    file.close();

    isSaved = true;
    ui->statusbar->showMessage(filename);
}

void MainWindow::saveFile(QPlainTextEdit *editor)
{
    if(filename.isEmpty())
    {
        saveFileAs();
        return;
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->editor->toPlainText();
    file.close();

    isSaved = true;
    ui->statusbar->showMessage(filename);
}

void MainWindow::saveFileAs(QPlainTextEdit *editor)
{
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString());
    if(temp.isEmpty()) return;
    filename = temp;
    saveFile();
}

