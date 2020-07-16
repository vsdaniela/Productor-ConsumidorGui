#include "productor.h"
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QRandomGenerator64>
productor::productor(int *a,const int &t,int *e,int *i,QObject *parent):QThread (parent), c_(a), total(t),e_pro(e),e_pro_i(i)
{

}
void productor::run()
{
    QMutex mMutex;
    int desperdicios=0;
    if(total>0){//buffer finito
        while(true){
          if(*c_<total){
            mMutex.lock();
            //bucket.push_back(1);
            //c++;
            *c_=*c_+1;
            *e_pro=*e_pro+1;
            emit elem_producidos(*e_pro);//elem producidoa
            emit valor_cambiado((*c_)*(100/total));//bucket
            mMutex.unlock();
          }
          else{
                std::uniform_int_distribution<int> distribution(1,500);
                int t=distribution(*QRandomGenerator::global());
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
           this->msleep(100);
          mMutex.lock();
          *c_=*c_+1;
          *e_pro_i=*e_pro_i+1;
          emit elem_producidos(*e_pro_i);//elem producidoa
          mMutex.unlock();

        }
    }
}

productor::~productor()
{
    qDebug()<<"se elimino\n";
}
