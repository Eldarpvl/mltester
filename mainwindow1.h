#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QAction>
#include <QCloseEvent>
#include <phonon>
#include <QPainter>
#include <QPixmap>

class QMenu;
class QSystemTrayIcon;

namespace Ui {
    class MainWindow1;
}
class Test;
class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = 0);
    ~MainWindow1();
    QString car, phone, home, mouse, pen;
    QString wr;
    int n;
    QString strArray[100][8];
    QPixmap pic;
    Ui::MainWindow1 *ui;
    QString level, category;
    Test *ekzam;
    QTimer *timer;
    bool b, b1;
    int counter;

public slots:
    void updateList();
    //void setInterval();
    void updateContent();
    void closeEvent(QCloseEvent *);

private:
    Phonon::MediaObject *music;
    int id;
    int idCount;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QMenu *intervalMenu;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *oneMin;
    QAction *fiveMin;
    QAction *tenMin;
    QAction *rMin;
    int time;

    int checkWord[5];
    int checkSenten[3];
    int repeatWords[100];
    QList <int> list;
    QList <int> numbers32;

private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void createTrayIcon();
    void minute1();
    void minute5();
    void minute10();
    void minuteR();

};

#endif // MAINWINDOW1_H
