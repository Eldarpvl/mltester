#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <cmath>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "test.h"
#include "ui_test.h"


MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    for(int i=0;i<32;i++){
        numbers32<<i;
    }
    ui->setupUi(this);
    timer = new QTimer(this);
    this->setWindowTitle("English Learning Software");
    //ui->label_29->setStyleSheet("background-color: rgb(116, 173, 170);");
    //ui->label_30->setStyleSheet("background-color: rgb(237, 236, 236);");
    ui->pushButton->setEnabled(false);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    level = ui->label_26->text();
    qDebug()<<level;
    category = ui->label_28->text();
    //updateList();
    //updateContent();
    createTrayIcon();
    trayIcon->show();
    b = false;
    b1 = false;
    qDebug()<<"Time: "<<time;
    counter = 0;
    ekzam = new Test;
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::updateList(){
    ui->listWidget->clear();
    QSqlQuery query;
    query.prepare("select * from Words where level = :level and category = :categ order by id");
    query.bindValue(":level", level);
    query.bindValue(":categ", category);
    query.exec();
    id=0;
    idCount = 0;
    while(query.next()){
        ui->listWidget->addItem(QString("%1: %2 - %3, %4, %5, %6, %7, %8").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString()).arg(query.value(3).toString()).arg(query.value(4).toString()).arg(query.value(5).toString()).arg(query.value(6).toString()).arg(query.value(7).toString()));
        id = query.value(0).toInt();
        strArray[idCount][0]=query.value(1).toString();
        strArray[idCount][1]=query.value(2).toString();
        strArray[idCount][2]=query.value(3).toString();
        strArray[idCount][3]=query.value(4).toString();
        strArray[idCount][4]=query.value(5).toString();
        strArray[idCount][5]=query.value(6).toString();
        strArray[idCount][6]=query.value(7).toString();
        idCount++;
    }
    qDebug()<<"id: "<<idCount;
    for(int i=0;i<idCount;i++){
        ui->label_21->setText(strArray[0][0]);
        qDebug()<<strArray[i][0]<<" "<<strArray[i][1]<<" "<<strArray[i][2]<<" "<<strArray[i][3]<<" "<<strArray[i][4]<<" "<<strArray[i][5]<<" "<<strArray[i][6];
    }
}

void MainWindow1::updateContent(){
    int random1=0;
    qDebug()<<"List size: "<<list.size()<<" Numbers32 size: "<<numbers32.size();

    if(numbers32.size()>1){
        for(int i=0;i<5;i++){
            if(i==0){
                if(list.size()>0){
                    if(list.size()-5==0){
                        random1 = qrand()%5;
                        qDebug()<<"list size: "<<list.size()<<", randomed number1: "<<random1;
                        checkWord[0]=list.at(random1);
                    }
                    else if(list.size()-5>0){
                        random1 = qrand()%3;
                        qDebug()<<"list size: "<<list.size()<<", randomed number1: "<<random1<<", "<<(list.size()-5)/3;
                        checkWord[0]=list.at(5+(list.size()-8)+random1);
                        //random1 = 5+(list.size()-5)/3*random1;
                    }
                    qDebug()<<random1;
                    qDebug()<<strArray[checkWord[0]][0];
                    ui->label->setText(strArray[checkWord[0]][0]);
                    ui->label_2->setText(strArray[checkWord[0]][1]);
                }
                else{
                    int r = qrand()%idCount;
                    //qDebug()<<r;
                    checkWord[0]=r;
                    ui->label->setText(strArray[r][0]);
                    ui->label_2->setText(strArray[r][1]);
                    qDebug()<<"First randomed number when list is empty: "<<r;
                    list.append(r);
                    numbers32.removeAt(r);
                }
            }
            if(i==1){
                if(list.size()-5==0 || list.size()-5>0){
                    if(list.size()-5==0){
                        int random2 = qrand()%5;
                        while(random2==random1){
                            random2 = qrand()%5;
                        }
                        qDebug()<<"list size: "<<list.size()<<", randomed number2: "<<random2;
                        checkWord[1] = list.at(random2);
                    }
                    else if(list.size()-5>0){
                        int random2 = qrand()%3;
                        while(random2 == random1){
                            random2 = qrand()%3;
                        }
                        qDebug()<<"list size: "<<list.size()<<", randomed number2: "<<random2<<", "<<(list.size()-5)/3;
                        checkWord[1]=list.at(5+(list.size()-8)+random2);
                    }
                    qDebug()<<strArray[checkWord[1]][0];
                    ui->label_3->setText(strArray[checkWord[1]][0]);
                    ui->label_4->setText(strArray[checkWord[1]][1]);
                }
                else{
                    qDebug()<<"Numbers32: "<<numbers32.size();
                    /*for(int i=0;i<numbers32.size();i++){
                        qDebug()<<"index: "<<i<<", "<<numbers32.at(i);
                    }*/
                    int r = qrand()%numbers32.size();
                    /*while(numbers32.at(r)==checkWord[0]){
                        r = qrand()%numbers32.size();
                    }*/
                    checkWord[1]=numbers32.at(r);
                    ui->label_3->setText(strArray[numbers32.at(r)][0]);
                    ui->label_4->setText(strArray[numbers32.at(r)][1]);
                    qDebug()<<"Second randomed number when list is empty: "<<numbers32.at(r);
                    list.append(numbers32.at(r));
                    numbers32.removeAt(r);
                }
            }
            if(i==2){
                qDebug()<<"Numbers32: "<<numbers32.size();
                int r = qrand()%numbers32.size();
                /*while(r==checkWord[0] || r==checkWord[1]){
                    r = qrand()%list.size();
                }*/
                checkWord[2]=numbers32.at(r);
                ui->label_5->setText(strArray[numbers32.at(r)][0]);
                ui->label_6->setText(strArray[numbers32.at(r)][1]);
                qDebug()<<"Randomed number(from "<<numbers32.size()<<"): "<<r<<", "<<numbers32.at(r);
                list.append(numbers32.at(r));
                numbers32.removeAt(r);
            }
            if(i==3){
                qDebug()<<"Numbers32: "<<numbers32.size();
                int r = qrand()%numbers32.size();
                /*while(r==checkWord[0] || r==checkWord[1] || r==checkWord[2]){
                    r = qrand()%list.size();
                }*/
                checkWord[3]=numbers32.at(r);
                ui->label_7->setText(strArray[numbers32.at(r)][0]);
                ui->label_8->setText(strArray[numbers32.at(r)][1]);
                qDebug()<<"Randomed number(from "<<numbers32.size()<<"): "<<r<<", "<<numbers32.at(r);
                list.append(numbers32.at(r));
                numbers32.removeAt(r);
            }
            if(i==4){
                qDebug()<<"Numbers32: "<<numbers32.size();
                int r = qrand()%numbers32.size();
                /*while(r==checkWord[0] || r==checkWord[1] || r==checkWord[2] || r==checkWord[3]){
                    r = qrand()%list.size();
                }*/
                checkWord[4]=numbers32.at(r);
                ui->label_9->setText(strArray[numbers32.at(r)][0]);
                ui->label_10->setText(strArray[numbers32.at(r)][1]);
                qDebug()<<"Randomed number(from "<<numbers32.size()<<"): "<<r<<", "<<numbers32.at(r);
                list.append(numbers32.at(r));
                numbers32.removeAt(r);
            }
        }

        qDebug()<<checkWord[0]<<" "<<checkWord[1]<<" "<<checkWord[2]<<" "<<checkWord[3]<<" "<<checkWord[4];
        qDebug()<<"List size before sentence"<<list.size();
        for(int i=0;i<3;i++){
            int check[3];
            if(i==0){
                if(list.size()==5){
                    int r = qrand()%5;
                    check[0]=r;
                    checkSenten[0]=checkWord[r];
                    ui->label_11->setText(strArray[checkWord[r]][2]);
                    qDebug()<<r;
                }
                else if(list.size()>5){
                    int r = qrand()%2;
                    checkSenten[0] = checkWord[r];
                    qDebug()<<"List size>5 : r = "<<r;
                    ui->label_11->setText(strArray[checkWord[r]][2]);
                }
            }
            if(i==1){
                if(list.size()==5){
                    int r = qrand()%5;
                    while(r==check[0]){
                        r = qrand()%5;
                    }
                    check[1]=r;
                    checkSenten[1] = checkWord[r];
                    ui->label_12->setText(strArray[checkWord[r]][2]);
                    qDebug()<<r;
                }
                else if(list.size()>5){
                    int r = qrand()%3;
                    check[1] = r;
                    checkSenten[1]=checkWord[r+2];
                    qDebug()<<"List size>5 : r = "<<r;
                    ui->label_12->setText(strArray[checkWord[r+2]][2]);
                }
            }
            if(i==2){
                if(list.size()==5){
                    int r = qrand()%5;
                    while(r==check[0] || r==check[1]){
                        r = qrand()%5;
                    }
                    check[2]=r;
                    checkSenten[2]=checkWord[r];
                    ui->label_13->setText(strArray[checkWord[r]][2]);
                    qDebug()<<r;
                }
                else if(list.size()>5){
                    int r = qrand()%3;
                    while(r==check[1]){
                        r = qrand()%3;
                    }
                    checkSenten[2]=checkWord[r+2];
                    qDebug()<<"List size>5 : r = "<<r;
                    ui->label_13->setText(strArray[checkWord[r+2]][2]);
                }
            }
        }
        qDebug()<<checkSenten[0]<<" "<<checkSenten[1]<<" "<<checkSenten[2];
    }
    else if(numbers32.size()<=1){
        QMessageBox msBox;
        msBox.setWindowTitle("title");
        msBox.setText("You did not end this course. Please choose the time interval and continue or exit.");
        msBox.setStandardButtons(QMessageBox::Close);
        msBox.exec();
        //if(msgBox.exec() == QMessageBox::Close){

        //}
        //this->close();
        //QMessageBox::information(this,tr(""),tr("Congratulations!!! You have end studying your course of English!!!"));
    }
}

void MainWindow1::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Words (id, word, translate, sentence) VALUES (:id, :word, :translate, :sentence)");
    id++;
    query.bindValue(":id", id);
    query.bindValue(":word", ui->lineEdit->text());
    query.bindValue(":translate", ui->lineEdit_2->text());
    query.bindValue(":sentence", ui->lineEdit_3->text());
    query.exec();
    updateList();
}

void MainWindow1::on_pushButton_2_clicked()
{
    updateContent();
}

void MainWindow1::createTrayIcon(){
    minimizeAction = new QAction(tr("Mi&nimize"),this);
    connect(minimizeAction, SIGNAL(triggered()),this,SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"),this);
    connect(maximizeAction,SIGNAL(triggered()),this,SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"),this);
    connect(restoreAction,SIGNAL(triggered()),this,SLOT(showNormal()));

    oneMin = new QAction(tr("1 min"),this);
    connect(oneMin,SIGNAL(triggered()),this,SLOT(minute1()));

    fiveMin = new QAction(tr("5 min"),this);
    connect(fiveMin,SIGNAL(triggered()),this,SLOT(minute5()));

    tenMin = new QAction(tr("10 min"),this);
    connect(tenMin,SIGNAL(triggered()),this,SLOT(minute10()));

    rMin = new QAction(tr("Choose..."),this);
    connect(rMin,SIGNAL(triggered()),this,SLOT(minuteR()));

    intervalMenu = new QMenu(tr("Interval"),this);
    intervalMenu->addAction(oneMin);
    intervalMenu->addAction(fiveMin);
    intervalMenu->addAction(tenMin);
    intervalMenu->addAction(rMin);

    quitAction = new QAction(tr("&Quit"),this);
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addMenu(intervalMenu);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QIcon(":/ECP");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip("Final Project");
}

//Timer
void MainWindow1::closeEvent(QCloseEvent *event){
    if(trayIcon->isVisible()){
        if(time==0){
            QMessageBox msgBox;
            msgBox.setWindowTitle("title");
            msgBox.setText("You did not end this course. Please choose the time interval and continue or exit.");
            msgBox.addButton(QMessageBox::Cancel);
            msgBox.addButton(QMessageBox::Close);
            msgBox.button(QMessageBox::Cancel)->setText("Continue");
            if(msgBox.exec() == QMessageBox::Cancel){
                event->ignore();
            }
        }
        else{
            hide();
            counter++;
            if(counter == 5){
                event->ignore();
                ekzam->show();
                //killTimer(timer->timerId());
                timer->stop();
                qDebug()<<b1;
                qDebug()<<ekzam->tf;
                while(ekzam->tf==true){
                    qDebug()<<ekzam->tf;
                    show();
                    break;
                }

            }
            else if(counter != 5 || counter != 10){
                event->ignore();
                //counter++;

                qDebug()<<time;
                //killTimer(time);
                connect(timer, SIGNAL(timeout()), this, SLOT(show()));
                timer->start(time*60000);
                pic = QPixmap(":/backPic");
                ui->label_35->setPixmap(pic);
                updateContent();

                qDebug()<<"Time of timer:"<<time<<", counter of opened window:"<<counter<<", Timer ID:"<<timer->timerId();
            }
        }
    }
}

//Code Guldany
/*void MainWindow1::setInterval(){
    oneMin->setChecked(false);
    fiveMin->setChecked(false);
    tenMin->setChecked(false);
    rMin->setChecked(false);
    QString intervalString = ((QAction*)sender())->text().mid(0,1);
    if(intervalString.startsWith("C")){
        rMin->setChecked(true);
        bool ok;
        double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                           tr("Minutes:"), 20, 5, 60, 0, &ok);
        if (ok)
                 time = d;
    }else{
        if(intervalString.startsWith("1"))
            oneMin->setChecked(true);
        else if(intervalString.startsWith("2"))
            fiveMin->setChecked(true);
        else
            tenMin->setChecked(true);
        time = intervalString.toInt();
        int startTime = QTime::currentTime().minute();
        while(true){
            int secondTime = QTime::currentTime().minute();
            if(secondTime-startTime>=time)
                this->show();
                qDebug()<<"ji";
                break;
        }
    }
}*/

void MainWindow1::minute1(){
    time = 1;
    qDebug()<<time;
}

void MainWindow1::minute5(){
    time = 5;
    qDebug()<<time;
}

void MainWindow1::minute10(){
    time = 10;
    qDebug()<<time;
}

void MainWindow1::minuteR(){
    QString text = QInputDialog::getText(this, tr("Input range number"),tr("Value :"), QLineEdit::Normal);
    time = text.toInt();
    qDebug()<<time;
}

void MainWindow1::on_pushButton_3_clicked()
{
    if(b==false){
        pic = QPixmap(":/"+ui->label->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        qDebug()<<filePath;
        music->play();
        b = true;
    }
    else if(b==true){
        music->stop();
        pic = QPixmap(":/"+ui->label->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
        b = true;
    }
}

void MainWindow1::on_pushButton_4_clicked()
{
    if(b==false){
        pic = QPixmap(":/"+ui->label_3->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_3->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
        b = true;
    }
    else if(b==true){
        music->stop();
        pic = QPixmap(":/"+ui->label_3->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_3->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
    }
}

void MainWindow1::on_pushButton_5_clicked()
{
    if(b==false){
        pic = QPixmap(":/"+ui->label_5->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_5->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
        b = true;
    }
    else if(b==true){
        music->stop();
        pic = QPixmap(":/"+ui->label_5->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_5->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
    }
}

void MainWindow1::on_pushButton_6_clicked()
{
    if(b==false){
        pic = QPixmap(":/"+ui->label_7->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_7->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
        b = true;
    }
    else if(b==true){
        music->stop();
        pic = QPixmap(":/"+ui->label_7->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_7->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
    }
}

void MainWindow1::on_pushButton_7_clicked()
{
    if(b==false){
        pic = QPixmap(":/"+ui->label_9->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_9->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
        b = true;
    }
    else if(b==true){
        music->stop();
        pic = QPixmap(":/"+ui->label_9->text());
        ui->label_35->setPixmap(pic);
        repaint();
        QString filePath = QCoreApplication::applicationDirPath() + "/words/"+ui->label_9->text()+".wav";
        music = Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource(filePath));
        music->play();
    }
}
