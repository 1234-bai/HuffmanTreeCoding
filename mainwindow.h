/************mainwindow.h**********/
//界面类定义

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "struct.h"

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
    void on_saveButton_clicked();

    void on_choseButton_clicked();

    void on_transButton_clicked();

private:
    Ui::MainWindow *ui;
    HuffmanTree HT;
    HuffmanCode HC;
    alph *atable;
    int num_char;
    int hash[257];
    bool is_yFile;
    bool have_chosedFile;
};
#endif // MAINWINDOW_H
