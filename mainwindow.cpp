#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    left_saved = true;
    connect(ui->actionOpen, &QAction::triggered,this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered,this, &MainWindow::saveFile);
    connect(ui->actionSaveAs, &QAction::triggered,this, &MainWindow::saveFileAs);


    right_saved = true;
    connect(ui->actionOpenRight, &QAction::triggered,this, &MainWindow::openFileRight);
    connect(ui->actionSaveRight, &QAction::triggered,this, &MainWindow::saveFileRight);
    connect(ui->actionSaveAsRight, &QAction::triggered,this, &MainWindow::saveFileAsRight);

    //newFile();
    //isSaved = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    ui->plainTextEdit->clear();
    filename.clear();
    ui->statusbar->showMessage("New File");
}

void MainWindow::openFile()
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
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();

    left_saved = true;
    ui->statusbar->showMessage(filename);
}

void MainWindow::saveFile()
{
    if(filename.isEmpty())
    {
        saveFileAs();
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();
    file.close();

    left_saved = true;
    ui->statusbar->showMessage(filename);
}

void MainWindow::saveFileAs()
{
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString());
    if(temp.isEmpty()) return;

    saveFile();
}

void MainWindow::newFileRight()
{
    ui->plainTextEditRight->clear();
    right_filename.clear();
    ui->statusbar->showMessage("New File");
    right_saved = false;
}

void MainWindow::openFileRight()
{
    QString temp = QFileDialog::getOpenFileName(this,"Open File",QString(),"Text Files (*txt);;All Files (*,*)");

    if(temp.isEmpty()) return;

    right_filename = temp;
    QFile file(right_filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        newFile();
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEditRight->setPlainText(stream.readAll());
    file.close();

    right_saved = true;
    ui->statusbar->showMessage(filename);
}

void MainWindow::saveFileRight()
{
    if(right_filename.isEmpty())
    {
        saveFileAs();
    }

    QFile file(right_filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->plainTextEditRight->toPlainText();
    file.close();

    right_saved = true;
    ui->statusbar->showMessage(right_filename);
}

void MainWindow::saveFileAsRight()
{
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString());
    if(temp.isEmpty()) return;

    saveFileRight();
}

