#include "diagram.h"
#include "ui_diagram.h"

Diagram::Diagram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diagram)
{
    ui->setupUi(this);

    Diagram::draw_diagram();
}

Diagram::~Diagram()
{
    delete ui;
}

QVector<double> Diagram::get_distribution(){

    QVector<double> distribution;
    long buffer[100];
    memset(buffer,0,sizeof(long)*100);

    /*Вычисляем значение параметра m в ЛКГ*/
    long m=1;
    for(int i=0;i<parametres::n;i++){
        m*=2;
    }
    /*получем длину интервала разбиения множества ПСЧ*/
    long intervalLen=m/100;

    /*распределяем сгенерированные ПСЧ по интервалам разбиения*/
    long leftBoard;
    long rightBoard;
    long b;

    for(long i=0;i<parametres::seqLen;i++){
        leftBoard=0;
        rightBoard=intervalLen;
        for(int j=0;j<100;j++){
            b=parametres::seq[i];
            if(b>=leftBoard && b<rightBoard ){
                buffer[j]+=1;
                break;
            }
            leftBoard=rightBoard;
            rightBoard+=intervalLen;
        }
    }

    /*вычисляем относительную частоту попадания ПСЧ в соответствующий интервал разбиения*/
    for(int i=0;i<100;i++){
        distribution.push_back((double)buffer[i]/parametres::seqLen*100);
    }

    return distribution;
}

void Diagram::get_min_man_max_distribution(QVector<double> distribution){

    double min=100;
    double max=0;
    double man=0;
    double counter=0;

    /* вычисялем максимальноую,онтосительную,минимальную частоты
     * распределения ПСЧ по интервалам разбиения
     */
    for(QVector<double>::iterator it=distribution.begin();it<distribution.end();it++){

        if(*it!=0){
            counter++;

            if(*it>max)
                max=*it;

            if(*it<min)
                min=*it;

            man+=*it;
        }
    }

    man/=counter;

    ui->outputMin->setPlainText(QString::number(min));
    ui->outputMan->setPlainText(QString::number(man));
    ui->outputMax->setPlainText(QString::number(max));
}

void Diagram::draw_diagram(){

    ui->customPlot->addGraph();
    QCPBars *newBars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);

    // Загружаем данные:
    QVector<double> xData(100),yData;
    for(int i=0; i<100;i++){
        xData[i]=i;
    }
    yData.append(Diagram::get_distribution());

    Diagram::get_min_man_max_distribution(yData);

    /*отрисовываем гистограмму*/
    ui->customPlot->xAxis->setLabel("интервал");
    ui->customPlot->yAxis->setLabel("частота(%)");
    ui->customPlot->xAxis->setRange(0, 100);
    ui->customPlot->yAxis->setRange(0, ui->outputMax->toPlainText().toInt());
    newBars->setData(xData, yData);
    ui->customPlot->replot();
}
