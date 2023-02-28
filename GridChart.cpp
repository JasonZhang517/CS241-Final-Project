#include <QBoxLayout>
#include <QSpinBox>
#include "GridChart.h"
GridChart::~GridChart()
{
}
GridChart::GridChart(QWidget* parent):QWidget(parent),numberOfOrders(100,0)
{
    //information part
    informationBtn=new QPushButton;
    informationBtn->setText(tr("What's this?"));
    connect(informationBtn,SIGNAL(clicked()),this,SLOT(showInformationMsg()));
    //initialize the chart
    timeStart=new QSpinBox(this);
    timeEnd=new QSpinBox(this);
    fieldEnd=new QLineEdit("end grid",this);
    fieldStart=new QLineEdit("start grid",this);
    dayStart=new QSpinBox(this);
    dayEnd=new QSpinBox(this);
    monthDisplay=new QLabel(this);
    yearDisplay=new QLabel(this);
    plotBtn=new QPushButton(this);
    plotBtn->setText("Plot");
    yearDisplay->setText("2016");
    monthDisplay->setText("11");
    timeStart->setPrefix("start from:");
    timeStart->setSuffix("hour");
    timeStart->setValue(0);
    timeStart->setRange(0,23);
    timeEnd->setPrefix("end by:");
    timeEnd->setSuffix("hour");
    timeEnd->setValue(23);
    timeEnd->setRange(0,23);
    dayStart->setPrefix("start from:");
    dayStart->setSuffix("day");
    dayStart->setValue(1);
    dayStart->setRange(1,14);
    dayEnd->setValue(15);
    dayEnd->setPrefix("end by:");
    dayEnd->setSuffix("day");
    dayEnd->setRange(1,15);
    //initialize the chart
    //chart settings
    auto chart= new QChart();
    chart->setTitle("The spacial demands in Chengdu City(Sorted by grids)");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //initializing
    initLayout();
}
void GridChart::initLayout(){
    auto mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(chartView);
    chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    auto spinLayout=new QVBoxLayout();
    // spinLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->addLayout(spinLayout);
    yearDisplay->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    monthDisplay->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    dayStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    dayEnd->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    timeStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    timeEnd->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    fieldStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    fieldEnd->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    plotBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    informationBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(yearDisplay);
    spinLayout->addWidget(monthDisplay);
    spinLayout->addWidget(dayStart);
    spinLayout->addWidget(dayEnd);
    spinLayout->addWidget(timeStart);
    spinLayout->addWidget(timeEnd);
    spinLayout->addWidget(fieldStart);
    spinLayout->addWidget(fieldEnd);
    spinLayout->addWidget(plotBtn);
    spinLayout->addWidget(informationBtn);
    connect(plotBtn,SIGNAL(clicked()),this,SLOT(loadData()));
}
void GridChart::updateChart(){
    auto chart=chartView->chart();
    auto left=fieldStart->text().toInt(), right=fieldEnd->text().toInt();
    chart->removeAllSeries();
    auto lineSeries= new QSplineSeries();
    auto scatterSeries= new QScatterSeries();
    for (int i=left;i<=right;++i){
        lineSeries->append(i,numberOfOrders[i]);
        scatterSeries->append(i,numberOfOrders[i]);
    }
    chart->addSeries(lineSeries);
    chart->addSeries(scatterSeries);
    //create the axies
    chart->createDefaultAxes();
    //xy axis
    auto xAxis= qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first());
    auto yAxis= qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    //details of the axis
    xAxis->setTitleText("grid");
    yAxis->setTitleText("num");
    xAxis->setRange(left,right);
    yAxis->setRange(yAxis->min() / 1.2, yAxis->max() * 1.2);
    }
void GridChart::getData(const DataSet& Data)
{
    newData=Data;
}
void GridChart::loadData()
{
    QDate startDate(2016,11,dayStart->value());
    QDate endDate(2016,11,dayEnd->value());
    QTime startTime(timeStart->value(),0,0,0);
    QTime endTime(timeEnd->value(),59,0,0);
    QDateTime start(startDate,startTime);
    QDateTime end(endDate,endTime);
    for(int i=0;i<100;i++)
    {numberOfOrders[i]=0;}
    if(start>end)
    {
        qDebug() << "invalid time input!";
        return;
    }
    for(int i=0;i<newData.size();i++)
    {
        int isize=newData[i]->size();
        for(int j=0;j<isize;j++)
        {
            if(fieldStart->text().toInt()>=0&&fieldStart->text().toInt()<=99&&fieldEnd->text().toInt()>=0&&fieldEnd->text().toInt()<=99)
            if(newData[i]->at(j).departure>=start&&newData[i]->at(j).end<=end)
            {
                int m = newData[i]->at(j).orig_gridid;
                if(m>=0&&m<=99)
                ++numberOfOrders[m];
            }
        }
    updateChart();
}
}
void GridChart::showInformationMsg()
{
    QMessageBox::information(this,tr("Explanation of the line Chart"),tr("the line chart displays the number of the orders according to the grid number \n the time and spacial range can be set via the boxes on the right\nClick the plot botton to see the updated chart"));
}
