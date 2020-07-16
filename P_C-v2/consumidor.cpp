#include "consumidor.h"
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QDebug>
#include <QRandomGenerator64>
consumidor::consumidor(int *a,const int &t,int *e, int*ei,QObject *parent):QThread (parent),total(t), e_con(e),e_con_i(ei)
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
            *e_con=*e_con+1;
            emit elem_consumidos(*e_con);//elementos consumidos
            emit valor_cambiado((*c_)*(100/total));//bucket
            mMutex.unlock();
          }
          else{
                std::uniform_int_distribution<int> distribution(1,500);
                int t=distribution(*QRandomGenerator::global());
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
            *e_con_i=*e_con_i+1;
            emit elem_consumidos(*e_con_i);//elementos consumidos
            mMutex.unlock();

          }
          this->msleep(200);
        }
    }
}
consumidor::~consumidor()
{
    qDebug()<<"se elimino\n";
}
