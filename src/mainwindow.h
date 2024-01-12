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
    //void colorSwitchedLines();
    //void colorDeletedLines();

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

    // Variables storing values for coloring
    std::tuple<std::map<int, std::string>,
               std::map<int, std::string>,
               std::vector<std::pair<int, int>>,
               std::vector<int>> resultOfTxtCompare;

    std::vector<std::pair<int, int>> switchedLines;
    std::map<int, std::string> deleted_lines;
    std::vector<int> modifications;

    static QString colorOfModification;
    static QString colorOfSwitchedLines;

    void colorModifications(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight);
    void colorSwitchedLines(QTextCursor& cursorTextLeft, QTextCursor& cursorTextRight);
    //void colorDeletedLines();
    void switchLinesFromLeftToRight(QPlainTextEdit* textEditorLeft, QPlainTextEdit* textEditorRight, int lineNumber);
    void setBlockColor(QTextDocument *txtDocument, QTextCursor &cursorTextLeft, QTextBlockFormat backgroundColor, int lineNumber);

};
#endif // MAINWINDOW_H
