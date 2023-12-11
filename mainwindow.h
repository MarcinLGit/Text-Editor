#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

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
    void newFile(QPlainTextEdit *editor);
    void openFile(QPlainTextEdit *editor);
    void saveFile(QPlainTextEdit *editor);
    void saveFileAs(QPlainTextEdit *editor);

private:
    Ui::MainWindow *ui;

    QString filename;
    bool isSaved;

    bool right_saved;
};
#endif // MAINWINDOW_H
