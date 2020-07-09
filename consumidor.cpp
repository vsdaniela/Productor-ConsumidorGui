#include "consumidor.h"
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QDebug>
consumidor::consumidor(int *a,const int &t,const int &e,QObject *parent):QThread (parent),total(t), e_con(e)
{
    c_=a;
}
void consumidor::run()
{
    int desperdicios=0;
    QMutex mMutex;
    if(total>0){
        while(true){
          if(*c_>=0){
            mMutex.lock();
            *c_=*c_-1;
            e_con++;
            emit elem_consumidos(e_con);//elementos consumidos
            emit valor_cambiado((*c_)*(100/total));//bucket
            mMutex.unlock();
          }
          else{
                unsigned long t=qrand();
                this->msleep(t);
                desperdicios+=t;
                emit lcd_tiempo_desperdicio(desperdicios);
                //std::this_thread::sleep_for(std::chrono::seconds(1));
          }
        }
    }
    else//buffer infinito
    {
        while(true){
          if(*c_>0){
            mMutex.lock();
            *c_=*c_-1;
            e_con++;
            emit elem_consumidos(e_con);//elementos consumidos
            mMutex.unlock();
          }
        }
    }
}
consumidor::~consumidor()
{
    qDebug()<<"se elimino\n";
}
