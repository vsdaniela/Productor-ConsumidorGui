#ifndef PC_H
#define PC_H

#include <QObject>
#include <QWidget>
#include <QThread>
class PC: public QThread
{
    Q_OBJECT
public:
    PC();
};

#endif // PC_H
