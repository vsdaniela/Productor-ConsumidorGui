#ifndef PRODUCTOR_H
#define PRODUCTOR_H

#include <QThread>
#include <QString>
#include <QLabel>
#include <QObject>
#include <QDebug>
class productor : public QThread
{
    Q_OBJECT
private:
    int temp_tiempo;
    int *c_=new int;
    int total;
    int *e_pro;
    int *e_pro_i;
public:
    explicit productor(int *a,const int &t,int *e,int *i,QObject *parent = nullptr);
    ~productor() override;
    void run() override;
signals:
    void valor_cambiado(int);//progress bar buffer
    void lcd_tiempo_desperdicioP(int);
    void elem_producidos(int);
    void label_terminado(QString);
};

#endif // PRODUCTOR_H
