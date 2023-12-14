#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    left_saved = true;
    connect(ui->actionOpenLeft, &QAction::triggered,this, &MainWindow::openFileLeft);
    connect(ui->actionSaveLeft, &QAction::triggered,this, &MainWindow::saveFileLeft);
    connect(ui->actionSaveAsLeft, &QAction::triggered,this, &MainWindow::saveFileAsLeft);
   // connect(ui->actionExit, &QAction::triggered,this, &MainWindow::close);

    right_saved = true;
    connect(ui->actionOpenRight, &QAction::triggered,this, &MainWindow::openFileRight);
    connect(ui->actionSaveRight, &QAction::triggered,this, &MainWindow::saveFileRight);
    connect(ui->actionSaveAsRight, &QAction::triggered,this, &MainWindow::saveFileAsRight);



    newFileLeft();
    left_saved = true;
    newFileRight();
    right_saved = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFileLeft()
{
    ui->plainTextEdit->clear();
    filename.clear();
    left_saved = false;
    ui->statusbar->showMessage("New File");
}

void MainWindow::openFileLeft()
{
    QString temp = QFileDialog::getOpenFileName(this,"Open File",QString(),"Text Files (*txt);;All Files (*,*)");

    if(temp.isEmpty()) return;

    filename = temp;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        newFileLeft();
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();

    left_saved = true;
    ui->statusbar->showMessage(filename);
}

void MainWindow::saveFileLeft()
{
    if(filename.isEmpty())
    {
        saveFileAsLeft();
        return;
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

void MainWindow::saveFileAsLeft()
{
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString());
    if(temp.isEmpty()) return;
    filename = temp;
    saveFileLeft();
}

void MainWindow::newFileRight()
{
    ui->plainTextEditRight->clear();
    right_filename.clear();
    right_saved = false;
    ui->statusbar->showMessage("New File");
}

void MainWindow::openFileRight()
{
    QString temp = QFileDialog::getOpenFileName(this,"Open File",QString(),"Text Files (*txt);;All Files (*,*)");

    if(temp.isEmpty()) return;

    right_filename = temp;
    QFile file(right_filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        newFileLeft();
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEditRight->setPlainText(stream.readAll());
    file.close();

    right_saved = true;
    ui->statusbar->showMessage(right_filename);
}

void MainWindow::saveFileRight()
{
    if(right_filename.isEmpty())
    {
        saveFileAsRight();
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
    right_filename = temp;
    saveFileRight();
}

