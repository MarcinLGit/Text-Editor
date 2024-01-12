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
#include <iostream>
#include <vector>
#include <map>

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

    QColor lightBlue(173, 216, 230);
    static QString colorOfModification = QString("background-color: %1").arg(lightBlue.name());
    QColor brightGreen(0, 255, 0);
    static QString colorOfNewLine = QString("background-color: %1").arg(brightGreen.name());
    QColor GreenSwapped(100, 255, 100);
    static QString colorOfSwapped = QString("background-color: %1").arg(GreenSwapped.name());

    QString buttonTextCompare = tr("Compare");
    QPushButton* buttonCompare;
    buttonCompare = new QPushButton(buttonTextCompare);
    //ui->tableWidget->setCellWidget(1,0,(QWidget*)buttonSwitchedLines);

    ui->verticalLayout->addWidget(buttonCompare);
    QObject::connect(buttonCompare, &QPushButton::clicked, this, &MainWindow::colorLines);

    //layout->insertRow(0, button2);
    //for(int i = 0; i<17; ++i){
    //   QString buttonText = tr("Button: #%1").arg(i);
    //   QPushButton* button2;
    //   button2 = new QPushButton(buttonText);
    //   ui->tableWidget->setCellWidget(i,0,(QWidget*)button2);
    //}

}

MainWindow::~MainWindow(){
    delete ui;
}

/**
 * @brief Ustawienie koloru linii
 *
 * Funkcja pomagająca w kolorwaniu różnic w tekscie bazując na numerach lini.
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


void MainWindow::switchLinesFromLeftToRight(QPlainTextEdit* textEditorLeft, QPlainTextEdit* textEditorRight, int lineNumber){
    // Get the document from both text editors
    QTextDocument* docLeft = textEditorLeft->document();
    QTextDocument* docRight = textEditorRight->document();

    // Create cursors for both documents
    QTextCursor cursorLeft(docLeft);
    QTextCursor cursorRight(docRight);

    // Move both cursors to the start of the document
    //cursorLeft.movePosition(QTextCursor::Start);
    //cursorRight.movePosition(QTextCursor::Start);

    QTextBlock blockLeft = docLeft->findBlockByLineNumber(lineNumber);
    QTextBlock blockRight = docRight->findBlockByLineNumber(lineNumber);
    cursorLeft.setPosition(blockLeft.position(), QTextCursor::MoveAnchor);
    cursorLeft.setPosition(blockLeft.position(), QTextCursor::KeepAnchor);
    //blockRight.setPosition(blockRight.position(), QTextCursor::MoveAnchor);
   // blockRight.setPosition(blockRight.position(), QTextCursor::KeepAnchor);
    //blockRight.ser
    // Store the text from the left line
   // QString lineText = cursorLeft.block().text();

    // Remove the line from the left editor
   //cursorLeft.removeSelectedText();

    // Insert the line into the right editor
   // cursorRight.insertText(lineText);
}


void MainWindow::colorSwitchedLines(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight){
    QTextBlockFormat backgroundClear;
    backgroundClear.clearBackground();

    for (const auto& pair : switchedLines) {
        std::cout << "Usunięcie" << pair.first << ", Zawartosc " << pair.second << std::endl; //TODELETE
    }

    for (const auto& pair: switchedLines) {
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundClear, pair.first);
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundClear, pair.second);

    }

    QColor lightRed(246, 246, 120);
    QTextBlockFormat backgroundColor;
    backgroundColor.setBackground(lightRed);

    switchedLines = std::get<2>(resultOfTxtCompare);
    for (const auto& pair : switchedLines) {
        std::cout << "Test: " << pair.first << ", Zawartosc " << pair.second << std::endl; //TODELETE
    }

    for (const auto& pair: switchedLines) {
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundColor, pair.first);
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundColor, pair.second);
    }
}

void MainWindow::colorModifications(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight){
  //  QTextCursor cursorTextLeft(ui->plainTextEdit->document());
   // QTextCursor cursorTextRight(ui->plainTextEditRight->document());


    QTextBlockFormat backgroundClear;
    backgroundClear.clearBackground();

    for(const int lineNum : modifications){
        std::cout << lineNum << std::endl;
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundClear, lineNum);
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundClear, lineNum);
    }


    QColor lightBlue(173, 216, 230);
    QTextBlockFormat backgroundColor;
    backgroundColor.setBackground(lightBlue);

    modifications = std::get<3>(resultOfTxtCompare);
    for(const int lineNum : modifications){
        std::cout << lineNum << std::endl;
        setBlockColor(ui->plainTextEdit->document(), cursorTextLeft, backgroundColor, lineNum);
        setBlockColor(ui->plainTextEditRight->document(), cursorTextRight, backgroundColor, lineNum);
    }
}

/**
 * @brief Funkcja kolorująca różnice w plikach
 *
 * Funkcja przekazuje wczytane przez użytkownika nazwy plików i przekazuje je od funkcji mainFuntion().
 * Wyniki operacji są zapisywane i wykorzystywane w uruchamianiu funkcji colorModifications i colorSwitchedLines.
 */
void MainWindow::colorLines(){
    resultOfTxtCompare = mainFunction(filename.toUtf8().constData(), right_filename.toUtf8().constData());
    QTextCursor cursorTextLeft(ui->plainTextEdit->document());
    QTextCursor cursorTextRight(ui->plainTextEditRight->document());
    colorModifications(cursorTextLeft, cursorTextRight);
    colorSwitchedLines(cursorTextLeft, cursorTextRight);
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
    std::cout << stream.encoding();
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

