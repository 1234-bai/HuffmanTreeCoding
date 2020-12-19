/***********mainwindow.cpp************/
//界面类的实现，按钮功能的实现

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "struct.h"
#include <QMessageBox>
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("HuffmanCode"));
    is_yFile = false;
    have_chosedFile = false;
    //建立哈夫曼编码树
   // HC = initHuffmanCode(26);
   // HT = HuffmanCoding(HC, alphtable, 26);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_saveButton_clicked()
{
    //获得存储位置和文件名
    QString fileName;
    if(!is_yFile) fileName = QFileDialog::getSaveFileName(this,tr("选取文件"),"/home",tr("编码文件(*.y)"));
    else fileName = QFileDialog::getSaveFileName(this,tr("选取文件"),"/home",tr("文本文件(*.txt)"));

    //获取输出框文件内容，并根据文件位置进行储存
    if (!fileName.isEmpty())
    {
        QString str = ui->to_textEdit->toPlainText();
        //如果是编码文件，就写入头数据，即字母表
        if(!is_yFile){
            //QMessageBox::information(this,tr("注意"),tr("开始写入头数据"));
            if(!write_headData_decodeFile((char*)fileName.toStdString().c_str(), atable, num_char)){
                QMessageBox::information(this,tr("注意"),tr("头数据写入失败"));
                return;
            }
        }
        if(saveStrToFile(fileName.toStdString().c_str(),str.toStdString().c_str())){
            ui->to_textEdit->clear();
            QMessageBox::information(this,tr("注意"),tr("保存成功"));
        }
        else
            QMessageBox::warning(this,tr("注意"),tr("保存失败"));
    }
}


void MainWindow::on_choseButton_clicked()
{
    //读取文件名
    memset(hash,-1,sizeof(hash));
    QString fileName = QFileDialog::getOpenFileName(this, tr("选取文件"), "/home", tr("文本文件( *.txt);;编码文件(*.y)"));
    if(fileName.isNull()){
        return;
    }
    std::string filename = fileName.toStdString();
    int len = fileName.length();
    QString str;
    alph* table;
    int n = 0;

    //区分文件类型
    if(fileName[len - 1] == 't'){
        is_yFile = false;
        //读取原始文件，获得字符串种类
        table = read_txtFile(filename.c_str(), hash, n);
        //QMessageBox::warning(this,tr("注意"),tr(filename.c_str()));
        //获得文件内容
        str = transFileToStr(filename.c_str());
    }
    else{
        is_yFile = true;
        //读取y文件
        table = read_yFile(filename.c_str(), str, &n);
    }
    if(n == 0){
        QMessageBox::warning(this,tr("注意"),tr("n==0"));
        return;
    }

    //获取字符种类数和字母表
    atable = table;
    num_char = n;
    //建树，建表
    HC = initHuffmanCode(n);
    HT = HuffmanCoding(HC, table, n);

    //将从文件获得的字符串在界面上输出
    if(str.isEmpty()){
        QMessageBox::warning(this,tr("注意"),tr("文件不存在或文件内容为空"));
    }
    else{
        have_chosedFile = true;
        ui->from_textEdit->setText(str);
    }
}

void MainWindow::on_transButton_clicked()
{
    //获得输入框的字符串
    ui->to_textEdit->clear();
    QString from_str = ui->from_textEdit->toPlainText();
    //if(!have_chosedFile) atable = read_txt(from_str.toStdString().c_str(), hash, num_char);

    //求取输出框的字符串
    QString to_str;
    //根据输入文件类型判断输入字符类型，后根据上面获得的哈夫曼树和表，进行转换
    if(from_str.isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("输入框为空或输入格式错误"));
        return;
    }
    else if(is_yFile)
        to_str = Huffman_decodeStr((char*)from_str.toStdString().c_str(), from_str.length(), HT, num_char, atable);
    else
        to_str = Huffman_codeStr((char*)from_str.toStdString().c_str(), HC, hash);

    //输出转换后的字符串
    if(to_str.isEmpty())
        QMessageBox::warning(this,tr("警告"),tr("输出为空"));
    else ui->to_textEdit->setText(to_str);
}
