#include "productor.h"
#include <QThread>
#include <QMutex>
#include <QObject>
productor::productor(int *a,const int &t,QObject *parent):QThread (parent), c_(a), total(t)
{

}
void productor::run()
{
    QMutex mMutex;
    int desperdicios=0;
    int e_pro=0;
    if(total>0){//buffer finito
        while(true){
          if(*c_<total){
            mMutex.lock();
            //bucket.push_back(1);
            //c++;
            *c_=*c_+1;
            e_pro++;
            emit elem_producidos(e_pro);//elem producidoa
            emit valor_cambiado((*c_)*(100/total));//bucket
            mMutex.unlock();
          }
          else{
                unsigned long t=qrand()%2000;
                this->msleep(t);
                desperdicios+=t;
                emit lcd_tiempo_desperdicioP(desperdicios);
                //std::this_thread::sleep_for(std::chrono::seconds(1));
          }
        }
    }
    else//buffer infinito
    {
        while(true){
          mMutex.lock();
          *c_=*c_+1;
          e_pro++;
          emit elem_producidos(e_pro);//elem producidoa
          mMutex.unlock();
        }
    }
}

productor::~productor()
{
    qDebug()<<"se elimino\n";
}
