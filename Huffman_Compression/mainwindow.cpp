#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Huffman.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("菜单");
    this->setFixedSize(this->width(),this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    textinput.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择日志文件"),"",tr("TXT(*.txt)"));
    if (fileName.isEmpty())     //如果未选择文件便确认，即返回
        return;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray line = file.readAll();
        QString gettext(line);
        string text1=q2s(gettext);
        QString fileName=QFileDialog::getSaveFileName(this,tr("保存文件"),"../filename","Text files (*.HuffmanZip)");
        QString outputt=Excute(text1,fileName);
        QMessageBox::about(this,"结果",outputt);

    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择日志文件"),"",tr("TXT(*.HuffmanZip)"));
    if (fileName.isEmpty())     //如果未选择文件便确认，即返回
        return;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QString temp;
        QString save_path=QFileDialog::getSaveFileName(this,tr("保存文件"),"../afterzip","Text files (*.txt)");
        temp = decode(fileName,save_path);
        QMessageBox::about(this,"解压结果",temp);
    }
}
