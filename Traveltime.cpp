#include<Traveltime.h>
aChart::~aChart()
{
}
Traveltime::~Traveltime()
{
}
aChart::aChart(QWidget* parent,int begin, int finish):QWidget(parent)
{
    for(int i=0;i<51;i++)
    {
        targetData1.append(0);
        targetData2.append(0);
        targetData3.append(0);
        targetData4.append(0);
        targetData5.append(0);
    }
    begindate=begin;
    finishdate=finish;
    start=new QSpinBox(this);
    end=new QSpinBox(this);
    informationBtn=new QPushButton;
    informationBtn->setText(tr("What's this?"));
    start->setValue(begin);
    end->setValue(finish);
    start->setPrefix("start: ");
    start->setSuffix(" th day");
    end->setPrefix("end: ");
    end->setSuffix(" th day");
    chart =new QChart();
    chart->setTitle("The Travelling Time of the Orders in Chengdu City");
    chart->legend()->hide();
    chartView->setChart(chart);
    chart->legend()->setAlignment(Qt::AlignBottom);
//    chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setTitle("The Travelling Time of the Orders in Chengdu City");
    QStringList categories;
    categories << "Day1" << "Day2" << "Day3" << "Day4" << "Day5";
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(QString("Day1"), QString("Day5"));
    chart->addAxis(axisY, Qt::AlignLeft);
    axisY->setRange(0, 5000);
    connect(informationBtn,SIGNAL(clicked()),this,SLOT(showInformationMsg()));
    initLayout();
}
void aChart::showInformationMsg()
{
    QMessageBox::information(this,tr("Explanation of the Bar Chart"),tr("the bar chart displays the time distribution of the orders,the time axis is divided in to 50 sections \n the higher the bar is, the more orders scattered in this time period \n the spinbox below can control the day range of the data"));
    return;
}
void aChart::updateChart()
{
    chart->removeAllSeries();
    QBarSeries *barseries=new QBarSeries();
    barseries->attachAxis(axisX);
    barseries->attachAxis(axisY);
    int starta=start->value();
    int enda=end->value();
    if(begindate==6)
    {starta=start->value()-5;enda=end->value()-5;}
    if(begindate==11)
    {starta=start->value()-10;enda=end->value()-10;}
    QString startString="Day";
    startString.append(QString::number(starta));
    QString endString="Day";
    endString.append(QString::number(enda));
    axisX->setRange(startString, endString);
    if(starta==1&&enda==5)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData1[i];
            *set << targetData2[i];
            *set << targetData3[i];
            *set << targetData4[i];
            *set << targetData5[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==2&&enda==5)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData2[i];
            *set << targetData3[i];
            *set << targetData4[i];
            *set << targetData5[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==3&&enda==5)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData3[i];
            *set << targetData4[i];
            *set << targetData5[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==4&&enda==5)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData4[i];
            *set << targetData5[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==5&&enda==5)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData5[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==1&&enda==1)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData1[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==1&&enda==2)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData1[i];
            *set << targetData2[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==1&&enda==3)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData1[i];
            *set << targetData2[i];
            *set << targetData3[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==1&&enda==4)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData1[i];
            *set << targetData2[i];
            *set << targetData3[i];
            *set << targetData4[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==2&&enda==4)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData2[i];
            *set << targetData3[i];
            *set << targetData4[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==2&&enda==3)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData2[i];
            *set << targetData3[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==2&&enda==2)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData2[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==3&&enda==3)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData3[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
    if(starta==3&&enda==4)
    {
        for(int i=0;i<=50;i++)
        {
            QBarSet *set=new QBarSet(QString::number(i*200));
            *set << targetData3[i];
            *set << targetData4[i];
            barseries->append(set);
        }
        chart->addSeries(barseries);
    }
}
void aChart::initLayout()
{
    auto mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(chartView);
    auto spinLayout=new QHBoxLayout(this);
    mainLayout->addLayout(spinLayout);
    spinLayout->addWidget(start);
    spinLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Ignored));
    spinLayout->addWidget(informationBtn);
    spinLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Ignored));
    spinLayout->addWidget(end);
    connect(start, QOverload<int>::of(&QSpinBox::valueChanged),this, &aChart::updateChart);
    connect(end,QOverload<int>::of(&QSpinBox::valueChanged),this, &aChart::updateChart);
}
void aChart::loadData(const DataSet &newData)
{
    for(int i=0;i<newData.size();i++)
    {
        int isize=newData[i]->size();
        for(int j=0;j<isize;j++)
        {
            int difference=newData[i]->at(j).departure.secsTo(newData[i]->at(j).end);
            int m=difference/200;
            if( m>=0 && m<=50)
            {
                if(newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, begindate))==0)
                targetData1[m]++;
                if(newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, begindate))==-1)
                targetData2[m]++;
                if(newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, begindate))==-2)
                targetData3[m]++;
                if(newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, begindate))==-3)
                targetData4[m]++;
                if(newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, begindate))==-4)
                targetData5[m]++;
            }
        }

    }
    updateChart();
}


Traveltime::Traveltime(QWidget* parent):QWidget(parent)
{
    list=new QListWidget(this);
    list->insertItem(0,tr("day 1-5"));
    list->insertItem(1,tr("day 6-10"));
    list->insertItem(2,tr("day 11-15"));
    chart1=new aChart(nullptr,1,5);
    chart2=new aChart(nullptr,6,10);
    chart3=new aChart(nullptr,11,15);
    stack=new QStackedWidget(this);
    stack->addWidget(chart1);
    stack->addWidget(chart2);
    stack->addWidget(chart3);
    auto mainLayout=new QHBoxLayout(this);
    list->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    stack->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));
}
void Traveltime::loadData(const DataSet& newData)
{
    chart1->loadData(newData);
    chart2->loadData(newData);
    chart3->loadData(newData);
}
