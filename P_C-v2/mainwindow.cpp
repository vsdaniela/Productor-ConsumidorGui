#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <productor.h>
#include <consumidor.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("D:/SO/P_C-SO/images_/consumidor.jpg");
    QPixmap pix_2("D:/SO/P_C-SO/images_/productor.jpg");

    ui->label->setPixmap(pix);
    ui->label_2->setPixmap(pix_2);
    ui->progressBar->setValue(0);
    ui->lcdNumber->display(0);
    ui->lcdNumber_2->display(0);
    ui->lcdNumber_4->display(0);
    ui->lcdNumber_5->display(0);
    c=new int;
    *c=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inicioButton_clicked()//consumidor
{
    QString c_num=ui->spinBox->text();
    int cn=c_num.toInt();
    int *e_c;
    int *e_i;
    e_c=new int;
    *e_c=0;
    e_i=new int;
    *e_i=0;
    if(ui->radioButton->isChecked())//finito
    {
        //sp2=total
        QString sp=ui->spinBox_2->text();
        total=sp.toInt();
        c1= new consumidor(c,total,e_c,e_i,this);
        c2= new consumidor(c,total,e_c,e_i,this);
        connect(c1,&consumidor::valor_cambiado,ui->progressBar,&QProgressBar::setValue);
        connect(c1,SIGNAL(lcd_tiempo_desperdicio(int)),ui->lcdNumber_4,SLOT(display(int)));//despedicios consumidor
        connect(c1,SIGNAL(elem_consumidos(int)),ui->lcdNumber_2,SLOT(display(int))); //elementos consumidos
        connect(c2,&consumidor::valor_cambiado,ui->progressBar,&QProgressBar::setValue);
        connect(c2,SIGNAL(lcd_tiempo_desperdicio(int)),ui->lcdNumber_4,SLOT(display(int)));
        connect(c2,SIGNAL(elem_consumidos(int)),ui->lcdNumber_2,SLOT(display(int))); //elementos consumidos
        if(cn==1)//caso 1 consumidor
        {
            c1->start();
        }
        if(cn==2)//caso 2 consumidores
        {
            c1->start();
            c2->start();
        }

    }
    if(ui->radioButton_2->isChecked())//infinito
    {
        c1= new consumidor(c,0,e_c,e_i,this);
        c2= new consumidor(c,0,e_c,e_i,this);
        connect(c1,&consumidor::valor_cambiado,ui->progressBar,&QProgressBar::setValue);
        connect(c1,SIGNAL(elem_consumidos(int)),ui->lcdNumber_2,SLOT(display(int))); //# consumidos
        connect(c2,&consumidor::valor_cambiado,ui->progressBar,&QProgressBar::setValue);
        connect(c2,SIGNAL(elem_consumidos(int)),ui->lcdNumber_2,SLOT(display(int))); //#consumidos
        if(cn==1)//caso 1 consumidor
        {
            c1->start();
        }
        if(cn==2)//caso 2 consumidores
        {
            c1->start();
            c2->start();
        }

    }
}

void MainWindow::on_inicio_productor_clicked()//inicio productor
{
    int *e_p;
    int *e_i;
    e_p=new int;
    *e_p=0;
    e_i=new int;
    *e_i=0;
    if(ui->radioButton->isChecked())//finito
    {
        QString sp=ui->spinBox_2->text();
        total=sp.toInt();
        p1= new productor(c,total,e_p,e_i,this);
        connect(p1,&productor::valor_cambiado,ui->progressBar,&QProgressBar::setValue);
        connect(p1,SIGNAL(lcd_tiempo_desperdicioP(int)),ui->lcdNumber_5,SLOT(display(int)));//desperdicios
        connect(p1,SIGNAL(elem_producidos(int)),ui->lcdNumber,SLOT(display(int)));//# producciones
        p1->start();

    }
    if(ui->radioButton_2->isChecked())//infinito
    {
        p1= new productor(c,0,e_p,e_i,this);
        connect(p1,&productor::valor_cambiado,ui->progressBar,&QProgressBar::setValue);
        connect(p1,SIGNAL(elem_producidos(int)),ui->lcdNumber,SLOT(display(int)));//# producciones
        p1->start();
    }
}
void MainWindow::on_pushButton_3_clicked()//fin productor
{
    p1->terminate();

}
void MainWindow::on_pushButton_clicked()//finconsumidor 1c
{

    c1->terminate();
}
void MainWindow::on_pushButton_2_clicked()
{
    c2->terminate();
}
