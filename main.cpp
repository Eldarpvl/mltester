#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtSql>
#include "mainwindow.h"
#include "mainwindow1.h"

bool connected(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbname = "C:/Qt/Examples/Adminka-build-desktop/debug/project.db";
    db.setDatabaseName(dbname);
    if(!db.open()) return false;

    QStringList tables = db.tables();

    if(!tables.contains("Words")){
        db.exec(QString("create table Words (id int, word VARCHAR(30), translate VARCHAR(30), sentence VARCHAR(30), sound VARCHAR(30), picture VARCHAR(30), level VARCHAR(30), category VARCHAR(30));"));
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!connected()){
        QMessageBox::warning(0, "DB ERROR", "Can not connect to Database");
        return 1;
    }
    MainWindow w;
    w.show();

    return a.exec();
}
