/**
 * @file mainwindow.h
 * @author Marcin Łobacz
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QHBoxLayout"
#include "logic4.h"
#include "QTextBlock"
#include <stdio.h>
#include <QDebug>
#include <QScrollBar>
const qint64 MAX_FILE_SIZE = 2 * 1024 * 1024;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    left_saved = true;
    connect(ui->actionOpenLeft, &QAction::triggered,this, &MainWindow::openFileLeft);
    connect(ui->actionSaveLeft, &QAction::triggered,this, &MainWindow::saveFileLeft);
    connect(ui->actionSaveAsLeft, &QAction::triggered,this, &MainWindow::saveFileAsLeft);

    right_saved = true;
    connect(ui->actionOpenRight, &QAction::triggered,this, &MainWindow::openFileRight);
    connect(ui->actionSaveRight, &QAction::triggered,this, &MainWindow::saveFileRight);
    connect(ui->actionSaveAsRight, &QAction::triggered,this, &MainWindow::saveFileAsRight);

    newFileLeft();
    left_saved = true;
    newFileRight();
    right_saved = false;

    QString buttonTextCompare = tr("Compare");
    QPushButton* buttonCompare;
    buttonCompare = new QPushButton(buttonTextCompare);
    ui->verticalLayout->addWidget(buttonCompare);
    connect(buttonCompare, &QPushButton::clicked, this, &MainWindow::colorLines);

    ui->tableButtons->horizontalHeader()->setDefaultSectionSize(25);
    ui->tableButtons->verticalHeader()->setDefaultSectionSize(15);
    // 30 20
    // synchronizacja skrolowania
    connect(ui->plainTextEdit->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->plainTextEditRight->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->plainTextEditRight->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->plainTextEdit->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->plainTextEdit->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->tableButtons->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->plainTextEditRight->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->tableButtons->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->tableButtons->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->plainTextEditRight->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->tableButtons->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->plainTextEdit->verticalScrollBar(), &QScrollBar::setValue);

    backgroundClear.clearBackground();

}

MainWindow::~MainWindow(){
    delete ui;
}

/**
 * @brief Ustawienie koloru linii
 *
 * Funkcja odpowaiada za kolorwanie różnic w tekście.
 *
 * @param txtDocument Wskaźnik do document
 * @param cursorText Przekazanie kursora tekstu
 * @param backgroundColor Kolor na jaki chcemy pomalować linię
 * @param lineNumber Numer lini do modyfikacji
*/
void MainWindow::setBlockColor(QTextDocument* txtDocument, QTextCursor& cursorText, QTextBlockFormat backgroundColor, int lineNumber){
    QTextBlock block = txtDocument->findBlockByLineNumber(lineNumber);
    cursorText.setPosition(block.position(), QTextCursor::MoveAnchor);
    cursorText.setPosition(block.position(), QTextCursor::KeepAnchor);
    cursorText.setBlockFormat(backgroundColor);

}

void MainWindow::deleteDeletedLine(){
    QPushButton *button = (QPushButton *)sender();
    int lineNumber = button->text().toUtf8().toInt();

    QTextBlock blockToDelete = ui->plainTextEdit->document()->findBlockByLineNumber(lineNumber);
    QTextCursor cursorTextLeft(ui->plainTextEdit->document());
    cursorTextLeft.setPosition(blockToDelete.position(), QTextCursor::MoveAnchor);
    cursorTextLeft.setPosition(blockToDelete.position()+blockToDelete.length(), QTextCursor::KeepAnchor);
    cursorTextLeft.removeSelectedText();

    delete button;
    colorLines();
}

void MainWindow::moveSwapedLine(QTextDocument* leftDoc, QTextDocument* rightDoc){
    QPushButton *button = (QPushButton *)sender();
    const QStringList btnTxt = button->text().split(':');
    const std::pair<int, int> lineNums = {btnTxt.at(0).toUtf8().toInt(), btnTxt.at(1).toUtf8().toInt()};

    QTextBlock blockToSwapLeft = leftDoc->findBlockByLineNumber(lineNums.first);
    QTextBlock blockToSwapRight = rightDoc->findBlockByLineNumber(lineNums.second);
    QTextCursor cursorTextLeft(leftDoc);

    cursorTextLeft.setPosition(blockToSwapLeft.position(), QTextCursor::MoveAnchor);
    cursorTextLeft.setPosition(blockToSwapLeft.position()+blockToSwapLeft.length(), QTextCursor::KeepAnchor);
    cursorTextLeft.removeSelectedText();

    cursorTextLeft.setPosition(blockToSwapRight.position(), QTextCursor::MoveAnchor);
    cursorTextLeft.setPosition(blockToSwapRight.position()+blockToSwapRight.length(), QTextCursor::KeepAnchor);
    cursorTextLeft.insertBlock();
    cursorTextLeft.selectedText() = blockToSwapRight.text();

}

/**
 * @brief MainWindow::moveSwapedLine Zamiana miejsca linijki wykrytej jako swapped.
 */
void MainWindow::moveSwappedLine(){
    QTextDocument* leftDoc = ui->plainTextEdit->document();
    QTextDocument* rightDoc = ui->plainTextEditRight->document();
    QPushButton *button = (QPushButton *)sender();
    const QStringList btnTxt = button->text().split(':');
    const std::pair<int, int> lineNums = {btnTxt.at(0).toUtf8().toInt(), btnTxt.at(1).toUtf8().toInt()};

    QTextBlock blockToSwapLeft = leftDoc->findBlockByLineNumber(lineNums.first);
    QTextBlock blockToSwapRight = rightDoc->findBlockByLineNumber(lineNums.second);
    QTextCursor cursorTextLeft(leftDoc);

    cursorTextLeft.setPosition(blockToSwapLeft.position(), QTextCursor::MoveAnchor);
    cursorTextLeft.setPosition(blockToSwapLeft.position()+blockToSwapLeft.length(), QTextCursor::KeepAnchor);
    cursorTextLeft.removeSelectedText();

    cursorTextLeft.setPosition(blockToSwapRight.position(), QTextCursor::MoveAnchor);
    cursorTextLeft.setPosition(blockToSwapRight.position(), QTextCursor::KeepAnchor);
    cursorTextLeft.insertText(blockToSwapRight.text() + "\n");

    QTextCursor cursorTextRight(rightDoc);
    setBlockColor(rightDoc, cursorTextRight, backgroundClear, lineNums.second);
    delete button;
    colorLines();
}

/**
 * @brief Funkcja kolorująca różnice w plikach
 *
 * Funkcja przekazuje wczytane przez użytkownika nazwy plików i przekazuje je od funkcji mainFuntion().
 * Wyniki operacji są zapisywane i wykorzystywane w uruchamianiu funkcji colorModifications i colorSwitchedLines.
 */
void MainWindow::colorLines(){

    QTextCursor cursorTextLeft(ui->plainTextEdit->document());
    QTextCursor cursorTextRight(ui->plainTextEditRight->document());

    std::vector<std::string> leftVec;
    std::vector<std::string> rightVec;
    QTextDocument *docleft = ui->plainTextEdit->document();
    QTextDocument *docRight = ui->plainTextEditRight->document();


    for (QTextBlock it = docleft->begin(); it != docleft->end(); it = it.next())
        leftVec.push_back(it.text().toUtf8().toStdString());

    for (QTextBlock it = docRight->begin(); it != docRight->end(); it = it.next()){
        rightVec.push_back(it.text().toUtf8().toStdString());
    }


    //qInfo() << leftVec;
    //qInfo() << rightVec;               TODELETE
    resultOfTxtCompare = mainFunction(leftVec, rightVec);
    // Resetowanie przycisków do łączenia tekstów
    ui->tableButtons->removeColumn(0);
    ui->tableButtons->removeColumn(1);
    ui->tableButtons->insertColumn(0);
    ui->tableButtons->insertColumn(1);

    // Przygotowanie rozmiaru tabeli do wstwiania przycików łączących teksty  
    ui->tableButtons->setRowCount(ui->plainTextEdit->document()->blockCount());
    colorAddedLines(cursorTextRight);
    colorDeletedLines(cursorTextLeft, cursorTextRight);
    colorModifications(cursorTextLeft, cursorTextRight);
    colorSwitchedLines(cursorTextLeft, cursorTextRight);
}

/**
 * @brief MainWindow::colorSwitchedLines Kolorwanie zamienionych linijek
 * @param cursorTextLeft
 * @param cursorTextRight
 */
void MainWindow::colorSwitchedLines(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight){
    QTextDocument* leftDoc = ui->plainTextEdit->document();
    QTextDocument* rightDoc = ui->plainTextEditRight->document();
    for (const auto& pair: switchedLines) {
        setBlockColor(leftDoc, cursorTextLeft, backgroundClear, pair.first);
        setBlockColor(rightDoc, cursorTextRight, backgroundClear, pair.second);

    }

    QColor lightYellow(246, 246, 120);
    QTextBlockFormat backgroundColor;
    backgroundColor.setBackground(lightYellow);

    switchedLines = std::get<2>(resultOfTxtCompare);
    for (const auto& pair: switchedLines) {
        setBlockColor(leftDoc, cursorTextLeft, backgroundColor, pair.first);
        setBlockColor(rightDoc, cursorTextRight, backgroundColor, pair.second);
        //qInfo() << "Switched: \n" << pair.first << ":" << pair.second;

        const QString txt = QString::number(pair.first) + ":" + QString::number(pair.second);
        QPushButton* buttonSwappingLines;
        buttonSwappingLines = new QPushButton(txt);
        buttonSwappingLines->setStyleSheet("background-color:rgb(246, 246, 120);");
        ui->tableButtons->setCellWidget(pair.first, 0, buttonSwappingLines);
        if(pair.first){
            ui->tableButtons->setRowHeight(0, 25);
        }
        connect(buttonSwappingLines, SIGNAL(clicked()), this, SLOT(moveSwappedLine()));
    }

}

/**
 * @brief MainWindow::colorAddedLines Kolorowanie dodanych lini
 * @param cursorTextLeft
 * @param cursorTextRight
 */
void MainWindow::colorAddedLines(QTextCursor &cursorTextRight){
    for (const auto& pair: addedLines) {
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundClear, pair.first);
    }

    QColor lightGreen(0, 255, 50);
    QTextBlockFormat backgroundColor;
    backgroundColor.setBackground(lightGreen);

    addedLines = std::get<0>(resultOfTxtCompare);
    for (const auto& pair: addedLines) {
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundColor, pair.first);
        //qInfo() << "Added: \n" << pair.first << ":" << pair.second;
    }
}

/**
 * @brief MainWindow::colorDeletedLines Koloruje linijki, które znajdują się w lewym edytorze i nie ma takich linijek w prawym edytorze.
 * @param cursorTextLeft
 * @param cursorTextRight
 */
void MainWindow::colorDeletedLines(QTextCursor &cursorTextLeft, QTextCursor &cursorTextRight){
    // Resetowanie kolorów tła
    for (const auto& pair: deletedLines) {
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundClear, pair.first);
    }

    QColor lightRed(255, 0, 0);
    QTextBlockFormat backgroundColor;
    backgroundColor.setBackground(lightRed);

    deletedLines = std::get<1>(resultOfTxtCompare);
    for (const auto& pair: deletedLines) {
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundColor, pair.first);
        QString txt = QString::number(pair.first);
        QPushButton* buttonTableTest;
        buttonTableTest = new QPushButton(txt);
        buttonTableTest->setStyleSheet("background-color: red");
        ui->tableButtons->setCellWidget(pair.first, 0, buttonTableTest);
        if(pair.first){
            ui->tableButtons->setRowHeight(0, 25);
        }
        connect(buttonTableTest, SIGNAL(clicked()), this, SLOT(deleteDeletedLine()));
        //qInfo() << "Deleted: \n" << pair.first << ":" << pair.second << "\n";
    }
}

/**
 * @brief MainWindow::colorModifications koloruje modyfikacje w kodzie.
 *
 * @param cursorTextLeft
 * @param cursorTextRight
 */
void MainWindow::colorModifications(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight){
    for(const int lineNum : modifications){
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundClear, lineNum);
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundClear, lineNum);
    }

    QColor lightBlue(173, 216, 230);
    QTextBlockFormat backgroundColor;
    backgroundColor.setBackground(lightBlue);

    modifications = std::get<3>(resultOfTxtCompare);
    for(const int lineNum : modifications){
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundColor, lineNum);
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundColor, lineNum);
        //qInfo() << "Modififcations: \n" << lineNum;
    }

}


/**
 * @brief Funkcja czyszcząca edytor tekstu znajdujący się po lewej stronie
*/
void MainWindow::newFileLeft(){
    ui->plainTextEdit->clear();
    filename.clear();
    left_saved = false;
    ui->statusbar->showMessage("New File");
}

/**
 * @brief Funkcja wczytuje plik do lewego edytora teksy
 *
 * Funkcja wczytuje pliki o maskymalnej wielkości 2 MB.
*/
void MainWindow::openFileLeft(){
    QString temp = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*txt);;All Files (*.*)");

    if(temp.isEmpty()) return;

    QFileInfo fileInfo(temp);
    const qint64 fileSize = fileInfo.size();

    if(fileSize > MAX_FILE_SIZE)
    {
        QMessageBox::critical(this, "Error", "The file size exceeds the limit.");
        return;
    }

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

/**
 * @brief Funkcja zapisuje tekst z lewego edytora do pliku
 *
 * Jeżeli przed zapisaniem nie wczytaliśmy żadnego pliku, funkcja wywołuje funkcję \ref MainWindow::saveFileAsLeft()
*/
void MainWindow::saveFileLeft(){
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
    stream.setEncoding(QStringConverter::Utf8);
    stream << ui->plainTextEdit->toPlainText();
    file.close();

    left_saved = true;
    ui->statusbar->showMessage(filename);
}

/**
 * @brief Funkcja zapisuje tekst z lewego edytora do wskazanego pliku
 *
 * Funkcja otwiera nowe okienko które pozwala na zapis do danego pliku lub nowo pliku.
*/
void MainWindow::saveFileAsLeft(){
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString());
    if(temp.isEmpty()) return;
    filename = temp;
    saveFileLeft();
}

/**
 * @brief Funkcja czyszcząca edytor tekstu znajdujący się po prawej stronie
*/
void MainWindow::newFileRight(){
    ui->plainTextEditRight->clear();
    right_filename.clear();
    right_saved = false;
    ui->statusbar->showMessage("New File");
}

/**
 * @brief Funkcja wczytuje plik do prawego edytora tekstu
 *
 * Funkcja wczytuje pliki o maskymalnej wielkości 2 MB.
*/
void MainWindow::openFileRight(){
    QString temp = QFileDialog::getOpenFileName(this,"Open File",QString(),"Text Files (*txt);;All Files (*.*)");

    if(temp.isEmpty()) return;

    QFileInfo fileInfo(temp);
    const qint64 fileSize = fileInfo.size();

    if(fileSize > MAX_FILE_SIZE)
    {
        QMessageBox::critical(this, "Error", "The file size exceeds the limit.");
        return;
    }

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

    ui->tableButtons->setRowCount(ui->plainTextEditRight->document()->blockCount());
    right_saved = true;
    ui->statusbar->showMessage(right_filename);
}

/**
 * @brief Funkcja zapisuje tekst z prawego edytora do pliku
 *
 * Jeżeli przed zapisaniem nie wczytaliśmy żadnego pliku, funkcja wywołuje funkcję \ref MainWindow::saveRightAsLeft()
*/
void MainWindow::saveFileRight(){
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
    stream.setEncoding(QStringConverter::Utf8);
    stream << ui->plainTextEditRight->toPlainText();
    file.close();

    right_saved = true;
    ui->statusbar->showMessage(right_filename);
}

/**
 * @brief Funkcja zapisuje tekst z prawego edytora do wskazanego pliku
 *
 * Funkcja otwiera nowe okienko które pozwala na zapis do danego pliku lub nowo utworzonego.
*/
void MainWindow::saveFileAsRight(){
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString());
    if(temp.isEmpty()) return;
    right_filename = temp;
    saveFileRight();
}

