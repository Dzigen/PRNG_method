#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "diagram.h"
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*инициализируем статические переменные*/
long* parametres::seq;
long parametres::seqLen;
long parametres::a;
long parametres::b;
long parametres::c0;

void MainWindow::generate_parameters(){

    QString time;
    QStringList timeSep;
    long timeInt[3];

    QString date;
    QStringList dateSep;
    long dateInt[3];

    /*значение даты и времени для генерации ПСЧ*/
    time=QTime::currentTime().toString();
    date=QDate::currentDate().toString("dd.MM.yyyy");

    timeSep=time.split(':');
    dateSep=date.split('.');

    for(int i=0; i<3; i++){
        timeInt[i]=timeSep.at(i).toInt();
        dateInt[i]=dateSep.at(i).toInt();
    }


    /*получаем значение параметры m в ЛКГ*/
    long m=1;
    for (int i=0;i<parametres::n;i++){
        m*=2;
    }

    /*генерируем параметры ЛКГ*/
    parametres::c0=(m/(timeInt[0]+timeInt[1]-1))/(timeInt[2]+1);

    long buffer=m/(1024+timeInt[2]);
    parametres::a=(buffer%4==1 ? buffer : (buffer-(buffer%4))+1);

    buffer=(m/(dateInt[1]+timeInt[1]+1))/(1024+timeInt[0]+1);
    while(true){
        if (buffer%2==0)
            buffer/=2;
        else
            break;
    }
    parametres::b=buffer;

    /*выводи значение в область главного окна*/
    ui->outputGeneratedParams->setText(QString("c0=")+QString::number(parametres::c0)+";a="+QString::number(parametres::a)+";b="+QString::number(parametres::b)+";");
}

void MainWindow::generate_sequence(long len){

    /*инициализируем область памяти для хранения ПСЧ*/
    parametres::seqLen=len;
    parametres::seq=(long*)malloc(sizeof(long)*len);
    memset(parametres::seq,0,sizeof(long));

    /*получаем значение параметры m в ЛКГ*/
    long m=1;
    for(int i=0;i<parametres::n;i++){
        m*=2;
    }

    long previous_number=parametres::c0;
    long current_number;

    int coloms=0;

    QString seqStr="";
    ui->outputSeq->setText(seqStr);

    QByteArray byteStr;
    QFile outFile("numbers.txt");
    outFile.open(QIODevice::WriteOnly);

    parametres::seq[0]=previous_number;

    seqStr.append(QString::number(parametres::seq[0])+" ");
    byteStr=QString::number(parametres::seq[0]).toUtf8()+" ";
    outFile.write(byteStr);
    coloms++;

    /*генерируем новое ПСЧ,выводим в окно главного меню и записываем в файл*/
    for(int i=1;i<len;i++){
        current_number=(parametres::a * previous_number+parametres::b)%m;

        if(coloms==7){
            coloms=0;

            ui->outputSeq->append(seqStr);
            seqStr="";

            outFile.write("\n");
        }

        seqStr.append(QString::number(current_number)+" ");
        byteStr=QString::number(current_number).toUtf8()+" ";
        outFile.write(byteStr);
        coloms++;

        parametres::seq[i]=current_number;
        previous_number=current_number;
    }

    ui->outputSeq->append(seqStr);
    outFile.close();
}

void MainWindow::on_buttonGenerateParams_released()
{
    /*инициализируем начальными значениями переменные*/
    ui->outputSeq->clear();
    ui->inputSeqLength->clear();
    ui->outputGeneratedParams->clear();
    ui->buttonViewDiagram->setEnabled(false);
    parametres::a=-1;
    parametres::b=-1;
    parametres::c0=-1;
    parametres::seqLen=-1;
    free(parametres::seq);

    MainWindow::generate_parameters();
}

void MainWindow::on_buttonGenerateSeq_released()
{
    ui->statusbar->showMessage("Генерируем ПСЧ...");
    ui->buttonGenerateSeq->setEnabled(false);
    MainWindow::generate_sequence(ui->inputSeqLength->toPlainText().toInt());
    ui->buttonGenerateSeq->setEnabled(true);
    ui->buttonViewDiagram->setEnabled(true);
    ui->statusbar->showMessage("Генерация ПСЧ завершена.");
}

void MainWindow::on_buttonViewDiagram_released()
{
    /*переходим в новое окно для отрисовки гистограммы*/
    Diagram dagrm;
    dagrm.setModal(true);
    dagrm.exec();
}
