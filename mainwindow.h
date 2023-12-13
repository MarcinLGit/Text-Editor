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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();

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
};
#endif // MAINWINDOW_H
