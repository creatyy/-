#ifndef INPUT_H
#define INPUT_H

#include <QMainWindow>

namespace Ui {
class Input;
}

class Input : public QMainWindow
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = nullptr);
    ~Input();

//private slots:
//    void on_pushButton_2_clicked();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Input *ui;
};

#endif // INPUT_H
