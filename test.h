#ifndef TEST_H
#define TEST_H

#include <QMainWindow>

namespace Ui {
    class Test;
}
class MainWindow1;
class Test : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    ~Test();
    Ui::Test *ui;
    MainWindow1 *mainn;
    bool tf;

private slots:
    void on_pushButton_clicked();
};

#endif // TEST_H
