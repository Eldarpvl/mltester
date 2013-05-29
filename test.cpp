#include "test.h"
#include "ui_test.h"
#include "mainwindow1.h"
#include "ui_mainwindow1.h"

Test::Test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);

}

Test::~Test()
{
    delete ui;
}

void Test::on_pushButton_clicked()
{
    mainn = new MainWindow1;
    //mainn->show()
    tf = true;
    //mainn->updateContent();
    this->hide();
    mainn->counter+1;
}
