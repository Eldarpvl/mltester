#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QFont>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("English Learning Software");
    this->setWindowIcon(QIcon(":/ECP"));
    main1 = new MainWindow1;
    QFont newFont("Sansation", 10);
    QApplication::setFont(newFont);
    ui->label->setStyleSheet("font-family: Sansation; font-size: 19px; color: white;");
    ui->label_2->setStyleSheet("font-family: Sansation; font-size: 14px; color: black;");
    ui->label_3->setStyleSheet("font-family: Sansation; font-size: 14px; color: black;");
    ui->label_4->setStyleSheet("font-family: Sansation; font-size: 14px; color: black;");
    //ui->label_7->setStyleSheet("font-family: Sansation light; font-size: 10px;");
    //ui->label_8->setStyleSheet("font-family: Sansation light; font-size: 10px;");
    ui->pushButton->setStyleSheet("color: white; background-color: rgb(116, 173, 170); border-radius: 5px;");
    ui->lineEdit->setAccessibleDescription("Type your name");
    ui->lineEdit->setStyleSheet("border: 3px solid rgb(116, 173, 170); border-radius: 2px; padding: 0 2px; selection-background-color: black;");
    ui->comboBox->setStyleSheet("QComboBox { border: 3px solid rgb(116, 173, 170); border-radius: 2px; padding: 1px 1px 1px 4px; min-width: 6em;} QComboBox::down-arrow { image: url(:/dd);}  QComboBox::down-arrow:on { top: 10px; left: 5px; }");
    ui->comboBox_2->setStyleSheet("QComboBox { border: 3px solid rgb(116, 173, 170); border-radius: 2px; padding: 1px 1px 1px 4px; min-width: 6em;} QComboBox::down-arrow { image: url(:/dd);}  QComboBox::down-arrow:on { top: 10px; left: 5px; }");
    //ui->comboBox_2->setStyleSheet("QComboBox { border: 1px solid gray; border-radius: 3px; padding: 1px 18px 1px 3px; min-width: 6em; } QComboBox:editable { background: white; } QComboBox:!editable, QComboBox::drop-down:editable { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); } QComboBox::}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    close();
    main1->show();
    if(ui->lineEdit->text().isEmpty()){
        main1->ui->label_24->setText("anonymous");
    }else{
        main1->ui->label_24->setText(ui->lineEdit->text());
    }
    main1->ui->label_26->setText(ui->comboBox->currentText());
    main1->level = ui->comboBox->currentText();
    main1->ui->label_28->setText(ui->comboBox_2->currentText());
    main1->category = ui->comboBox_2->currentText();
    main1->updateList();
    main1->updateContent();
}
