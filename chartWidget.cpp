#include <QBoxLayout>
#include <QSpinBox>
#include "chartWidget.h"

ChartWidget::~ChartWidget(){}
ChartWidget::ChartWidget(QWidget* parent):QWidget(parent),numberOfOrders(30,0)
{
    //information part
    informationBtn=new QPushButton;
    informationBtn->setText(tr("What's this?"));
    connect(informationBtn,SIGNAL(clicked()),this,SLOT(showInformationMsg()));
    //initialize the chart
//    start=new QSpinBox(this);
//    end=new QSpinBox(this);
    //the controlling part
    timeStart=new QSpinBox(this);
    timeEnd=new QSpinBox(this);
    fieldEnd=new QLineEdit("end grid",this);
    fieldStart=new QLineEdit("start grid",this);
    dayStart=new QSpinBox(this);
    dayEnd=new QSpinBox(this);
    monthDisplay=new QLabel(this);
    yearDisplay=new QLabel(this);
    plotBtn=new QPushButton(this);
    setStep=new QComboBox(this);
    FeeDisplay=new QLabel(this);
    setStep->addItem("day");
    setStep->addItem("hour");
    plotBtn->setText("Plot");
    yearDisplay->setText("2016");
    monthDisplay->setText("11");
    FeeDisplay->setText("total revenue: ");
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
    dayStart->setRange(1,15);
    dayEnd->setValue(15);
    dayEnd->setPrefix("end by:");
    dayEnd->setSuffix("day");
    dayEnd->setRange(1,15);
    //end
//    start->setValue(1);
//    end->setValue(15);
//    start->setPrefix("start: ");
//    start->setSuffix(" th day");
//    end->setPrefix("end: ");
//    end->setSuffix(" th day");
    //details of the chart
    auto chart= new QChart();
    chart->setTitle("The number of orders in Chengdu City over time");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //initializing
    //updateChart();
    initLayout();
}
void ChartWidget::updateChart(){
    if(setStep->currentText()=="day")
    {
        QString fee="total revenue: ";
        fee.append(QString::number(totalRevenue));
        FeeDisplay->setText(fee);
        auto chart=chartView->chart();
        auto left=dayStart->value(), right=dayEnd->value();
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
        xAxis->setTitleText("day");
        yAxis->setTitleText("num");
        xAxis->setRange(left,right);
        yAxis->setRange(yAxis->min() / 1.2, yAxis->max() * 1.2);
        //signal of changes
//        dayStart->setRange(1,right-1);
//        dayEnd->setRange(left+1,15);
    }
    if(setStep->currentText()=="hour")
    {
        QString fee="total revenue: ";
        fee.append(QString::number(totalRevenue));
        FeeDisplay->setText(fee);
        auto chart=chartView->chart();
        auto left=timeStart->value(), right=timeEnd->value();
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
        xAxis->setTitleText("hour");
        yAxis->setTitleText("num");
        xAxis->setRange(left,right);
        yAxis->setRange(yAxis->min() / 1.2, yAxis->max() * 1.2);
        //signal of changes
        timeStart->setRange(0,right-1);
        timeEnd->setRange(left+1,23);
    }
    }
void ChartWidget::initLayout(){
    auto mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(chartView);
    chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    auto spinLayout=new QVBoxLayout();
    spinLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->addLayout(spinLayout);
    setStep->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(setStep);
    yearDisplay->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(yearDisplay);
    monthDisplay->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(monthDisplay);
    FeeDisplay->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(FeeDisplay);
    dayStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(dayStart);
    dayEnd->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(dayEnd);
    timeStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(timeStart);
    timeEnd->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(timeEnd);
    fieldStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(fieldStart);
    fieldEnd->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(fieldEnd);
    plotBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(plotBtn);
    informationBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    spinLayout->addWidget(informationBtn);
    connect(plotBtn,SIGNAL(clicked()),this,SLOT(loadData()));
}
void ChartWidget::getData(const DataSet& Data)
{
    newData=Data;
}
void ChartWidget::loadData() {
    totalRevenue=0;
    if(setStep->currentText()=="day")
    {
        QDate startDate(2016,11,dayStart->value());
        QDate endDate(2016,11,dayEnd->value());
        QTime startTime(0,0,0,0);
        QTime endTime(23,59,0,0);
        QDateTime start(startDate,startTime);
        QDateTime end(endDate,endTime);
        for(int i=0;i<30;i++)
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
                if(newData[i]->at(j).departure>=start&&newData[i]->at(j).end<=end)
                {
                    int m = 1 -newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, 1));
                    ++numberOfOrders[m];
                    totalRevenue+=newData[i]->at(j).fee;
                }
            }
        }
        updateChart();
    }
    if(setStep->currentText()=="hour")
    {
        QDate startDate(2016,11,dayStart->value());
        QDate endDate(2016,11,dayEnd->value());
        QTime startTime(timeStart->value(),0,0,0);
        QTime endTime(timeEnd->value(),59,0,0);
        QDateTime start(startDate,startTime);
        QDateTime end(endDate,endTime);
        for(int i=0;i<30;i++)
        {numberOfOrders[i]=0;}
        if(start>end||startDate!=endDate)
        {
            qDebug() << "invalid time input!";
            return;
        }
        for(int i=0;i<newData.size();i++)
        {
            int isize=newData[i]->size();
            for(int j=0;j<isize;j++)
            {
                if(newData[i]->at(j).departure>=start&&newData[i]->at(j).end<=end)
                {
                    int m = newData[i]->at(j).departure.time().hour();
                    ++numberOfOrders[m];
                    totalRevenue+=newData[i]->at(j).fee;
                }
            }
        updateChart();
    }
    }
}
void ChartWidget::showInformationMsg()
{
    QMessageBox::information(this,tr("Explanation of the line Chart"),tr("the line chart displays the number of the orders according to the date\n The combobox can set the time step of the display \n Click the plot botton to see the updated chart"));
}
