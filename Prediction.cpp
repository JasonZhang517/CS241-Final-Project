#include <QBoxLayout>
#include <QSpinBox>
#include <QString>
#include "Prediction.h"
bool operator<(const pair &s1,const pair&s2)
{
    return s1.key<s2.key;
}
bool operator>(const pair &s1,const pair&s2)
{
    return s1.key>s2.key;
}
Prediction::~Prediction()
{

}
Prediction::Prediction(QWidget* parent):QWidget(parent)
{
    //information part
    informationBtn=new QPushButton;
    informationBtn->setText(tr("What's this?"));
    connect(informationBtn,SIGNAL(clicked()),this,SLOT(showInformationMsg()));
    //initialize
    pair a;
    time=0;
    qualifiedOrders=0;
    totalfee=0;
    a.key=0;
    a.gridid=0;
    for(int i=0;i<100;i++)
    {
        pair* newpair=new pair();
        newpair->gridid=i;
        newpair->key=0;
        targetData.append(*newpair);
    }
    start=new QSpinBox(this);
    end=new QSpinBox(this);
    start->setValue(1);
    end->setValue(15);
    start->setPrefix("start: ");
    start->setSuffix(" (day)");
    end->setPrefix("end: ");
    end->setSuffix(" (day)");
    //chart settings
    auto chart= new QChart();
    chart->setTitle("The Proportion of Spacial demands in Chengdu City(Sorted by grids)");
    chart->legend()->hide();
    //initializing
    initLayout();
}
void Prediction::initLayout(){
    auto mainLayout=new QVBoxLayout(this);
    auto topLayout=new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    Origin=new QLabel(tr("Origin: (grid number)"));
    Destination=new QLabel(tr("Destination: (grid number)"));
    OriginInput=new QLineEdit(QString::number(55));
    DestinationInput=new QLineEdit(QString::number(55));
    Probable=new QLabel(tr("Probable Destination: (grid number)"));
    Average=new QLabel(tr("Average Time"));
    DestDisplay=new QLabel(tr(" (grid number)"));
    TimeDisplay=new QLabel(tr("0(time)"));
    Calculate= new QPushButton(tr("Predict"));
    FeeDisplay=new QLabel(tr("0(fee)"));
    topLayout->addWidget(informationBtn);
    topLayout->addWidget((Origin));
    topLayout->addWidget((OriginInput));
    topLayout->addWidget((Destination));
    topLayout->addWidget((DestinationInput));
    topLayout->addWidget((Probable));
    topLayout->addWidget(DestDisplay);
    topLayout->addWidget(Average);
    topLayout->addWidget(TimeDisplay);
    topLayout->addWidget(FeeDisplay);
    topLayout->addWidget(Calculate);
    auto spinLayout=new QHBoxLayout();
    mainLayout->addLayout(spinLayout);
    spinLayout->addWidget(start);
    spinLayout->addSpacerItem(new QSpacerItem(600,1000,QSizePolicy::Expanding, QSizePolicy::Ignored));
    spinLayout->addWidget(end);
    QObject::connect(Calculate,SIGNAL(clicked()),this,SLOT(loadData()));
}
void Prediction::updateData(){
    auto left=start->value(), right=end->value();
    sortedData=targetData;
    std::stable_sort(sortedData.begin(),sortedData.end(),std::greater<pair>());
    auto DesttoDisplay=QString::number(sortedData.begin()->gridid);
    DesttoDisplay.append("\n");
    DesttoDisplay.append(QString::number(sortedData[1].gridid));
    DesttoDisplay.append("\n");
    DesttoDisplay.append(QString::number(sortedData[2].gridid));
    DesttoDisplay.append(" (First 3 possible grid number)");
    DestDisplay->setText(DesttoDisplay);
    double averageTime=time/qualifiedOrders;
    double averageFee=totalfee/qualifiedOrders;
    QString time=QString::number(averageTime);
    time.append("(estimated time)");
    QString fee=QString::number(averageFee);
    fee.append("(estimated fee)");
    TimeDisplay->setText(time);
    FeeDisplay->setText(fee);
    //signal of changes
    start->setRange(1,right-1);
    end->setRange(left+1,15);
    }
void Prediction::loadData(const DataSet &newData,int origGrid,int destGrid)
{
    for(int i=0;i<100;i++)
    {
        targetData[i].key=0;
    }
    time=0;
    qualifiedOrders=0;
    for(int i=0;i<newData.size();i++)
    {
        int isize=newData[i]->size();
        for(int j=0;j<isize;j++)
        {
             if(1-newData[i]->at(j).departure.date().daysTo(QDate(2016, 11, 1))>=start->value()&&
                     1-newData[i]->at(j).end.date().daysTo(QDate(2016, 11, 1))<=end->value()) {
             int m = newData[i]->at(j).dest_gridid;
             int n = newData[i]->at(j).orig_gridid;
             if (m >= 0 && m < 100 && n==origGrid)
             {
                 targetData[m].key++;
             }
             if((m >= 0 && m < 100 && n==origGrid)&&m==destGrid)
             {
                 qualifiedOrders++;
                 time+=newData[i]->at(j).departure.secsTo(newData[i]->at(j).end);
                 totalfee+=newData[i]->at(j).fee;
             }
             }
        }
    }
    updateData();
}
void Prediction::loadData(const DataSet &newData)
{
    int origGrid=OriginInput->text().toInt();
    int destGrid=DestinationInput->text().toInt();
    loadData(newData,origGrid,destGrid);
    savedData=newData;
}
void Prediction::loadData()
{
    loadData(savedData);
}
void Prediction::showInformationMsg()
{
    QMessageBox::information(this,tr("Explanation of the module"),tr("the module can predict your possible destination according to your origin, offering 3 most possible solutions \n With a destination provided, possible time can be predicted based on the given data \n the default grid is the busiest grid, Grid 55,which can be customly changed"));
}
