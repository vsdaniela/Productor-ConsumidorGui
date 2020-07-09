#ifndef CONSUMIDOR_H
#define CONSUMIDOR_H

#include <QThread>
#include <QString>
#include <QLabel>
#include <QObject>
#include <QDebug>
class consumidor: public QThread
{
    Q_OBJECT
private:
    int *c_=new int;
    int e_con;
    int total;

public:
    explicit consumidor(int *a,const int &t,const int &e,QObject *parent = nullptr);
    ~consumidor() override;
    void run() override;
signals:
    void valor_cambiado(int);//progress bar buffer
    void lcd_tiempo_desperdicio(int);
    void elem_consumidos(int);
    void label_terminado(QString);
};

#endif // CONSUMIDOR_H
