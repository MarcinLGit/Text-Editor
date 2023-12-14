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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    /**
     * @brief Usuwa tekst z lewego dytora
     */
    void newFileLeft();
    /**
     * @brief Otwiera nowy plik, wczytuje plik do lewego edytora
     */
    void openFileLeft();
    /**
     * @brief Zapisuje modyfikacje pliku.
     */
    void saveFileLeft();
    /**
     * @brief Zapisywanie tesktu lewego edytora do pliku
     */
    void saveFileAsLeft();

    /**
     * @brief Usuwa tekst z lewego dytora
     */
    void newFileRight();
    /**
     * @brief Otwiera nowy plik, wczytuje plik do lewego edytora
     */
    void openFileRight();
     /**
     * @brief Zapisuje modyfikacje pliku.
     */
    void saveFileRight();
    /**
     * @brief Zapisywanie tesktu prawego edytora do pliku
     */
    void saveFileAsRight();


private:
    Ui::MainWindow *ui;

    QString filename;
    bool left_saved;

    QString right_filename;
    bool right_saved;
};
#endif // MAINWINDOW_H
