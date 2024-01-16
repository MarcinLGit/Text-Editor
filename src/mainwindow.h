/**
 * @file mainwindow.h
 *
 * @author Marcin Łobacz 
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QPlainTextEdit>
#include <stdio.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/**
 * @brief Główne okno programu
 */
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:


    void colorLines();
    void deleteDeletedLine();

    void newFileLeft();
    void openFileLeft();
    void saveFileLeft();
    void saveFileAsLeft();

    void newFileRight();
    void openFileRight();
    void saveFileRight();
    void saveFileAsRight();


private:
    Ui::MainWindow *ui;

    QString filename;
    bool left_saved;

    QString right_filename;
    bool right_saved;

    std::pair<std::vector<std::string>, std::vector<std::string>> files;

    // Variable storing values for coloring
    std::tuple<std::map<int, std::string>,
               std::map<int, std::string>,
               std::vector<std::pair<int, int>>,
               std::vector<int>> resultOfTxtCompare;

    std::map<int, std::string> deletedLines;
    std::map<int, std::string> addedLines;
    std::vector<std::pair<int, int>> switchedLines;
    std::vector<int> modifications;

    std::vector<int> coloredBlocks;
    void colorModifications(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight);
    void colorSwitchedLines(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight);
    void colorAddedLines(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight);
    void colorDeletedLines(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight);

    void setBlockColor(QTextDocument *txtDocument, QTextCursor &cursorTextLeft, QTextBlockFormat backgroundColor, int lineNumber);
};
#endif // MAINWINDOW_H
