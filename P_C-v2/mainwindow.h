#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <productor.h>
#include <consumidor.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inicioButton_clicked();

    void on_pushButton_clicked();

    void on_inicio_productor_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int *c;
    int total;
    productor *p1;
    consumidor *c1;
    consumidor *c2;
};

#endif // MAINWINDOW_H
