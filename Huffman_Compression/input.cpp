#include "input.h"
#include "ui_input.h"
#include "string"
#include "QDebug"
#include "QMessageBox"
#include "Huffman.h"
#include <QTextStream>

Input::Input(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
    this->setWindowTitle("文本输入");
    this->setFixedSize(this->width(),this->height());
}

Input::~Input()
{
    delete ui;
}

void Input::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText()=="")
        QMessageBox::information(this,"错误","请输入内容！");
    else{
        QString text=ui->textEdit->toPlainText();
        string temp = q2s(text);
        QString fileName=QFileDialog::getSaveFileName(this,tr("保存文件"),"../filename","Text files (*.HuffmanZip)");
        QString outputt=Excute(temp,fileName);
        QMessageBox::about(this,"结果",outputt);
    }
}

void Input::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
}
