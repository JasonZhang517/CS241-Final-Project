#include "mainwindow.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <input_controlling_layout.h>
#include <QProgressDialog>
#include <QFont>
#include <QDir>
#include <QMetaType>
inputControlling::inputControlling(QWidget* parent):QWidget(parent)
{
    qRegisterMetaType<OrderInformation>("OrderInformation");
    qRegisterMetaType<QVector<OrderInformation>>("QVector<OrderInformation>");
    //input data
    count=75;
    fileBtn=new QPushButton;
    fileBtn->setText(tr("载入数据(CSV文件)"));
    lineEdit=new QLabel;
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(fileBtn,0,0);
    mainLayout->addWidget(lineEdit,2,0);
    connect(fileBtn,SIGNAL(clicked()),this,SLOT(loadCSV()));
    //set the range of the data
//    timeStart=new QSpinBox(this);
//    timeEnd=new QSpinBox(this);
//    fieldEnd=new QLineEdit(this);
//    fieldStart=new QLineEdit(this);
//    dayStart=new QSpinBox(this);
//    dayEnd=new QSpinBox(this);
//    monthDisplay=new QLabel(this);
//    yearDisplay=new QLabel(this);
//    mainLayout->addWidget(yearDisplay,4,0);
//    mainLayout->addWidget(monthDisplay,6,0);
//    mainLayout->addWidget(dayStart,8,0);
//    mainLayout->addWidget(dayEnd,10,0);
//    mainLayout->addWidget(timeStart,12,0);
//    mainLayout->addWidget(timeEnd,14,0);
//    mainLayout->addWidget(fieldStart,16,0);
//    mainLayout->addWidget(fieldEnd,18,0);
//    yearDisplay->setText("2016");
//    timeStart->setPrefix("start from:");
//    timeStart->setSuffix("hour");
//    timeStart->setValue(0);
//    timeStart->setRange(0,23);
//    timeEnd->setPrefix("end by:");
//    timeEnd->setSuffix("hour");
//    timeEnd->setValue(24);
//    timeEnd->setRange(1,24);
//    dayStart->setPrefix("start from:");
//    dayStart->setSuffix("day");
//    dayStart->setValue(1);
//    dayEnd->setValue(15);
//    dayEnd->setPrefix("end by:");
//    dayEnd->setSuffix("day");
//    int dayRight=dayEnd->value();
//    dayStart->setRange(0,dayRight);
//    int dayLeft=dayStart->value();
//    dayEnd->setRange(dayLeft,15);
    connect(this,SIGNAL(complete()),this,SLOT(finished()));
}
void inputControlling::receive(Data* re)
{
    count--;
    // emit passBar(count);
    progressDialog->setValue(75-count);
    Dataset.push_back(re);
    if (count == 0)
        emit complete();
}
void inputControlling::finished()
{
    emit passing(&Dataset);
}
void inputControlling::loadCSV()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this, "Open File", ".", "CSV Files (*.csv)");
    initializeBar();
    for(int i=1;i<=15;i++)
    {
        QString newName="201611";
        if(i<10)
        {
            newName.append("0");
        }
        newName.append(QString::number(i));
        QStringList newDay=fileName.filter(newName);
        readThread[i]=new importThread(newDay);
        connect(readThread[i],SIGNAL(release(Data*)),this,SLOT(receive(Data*)));
        readThread[i]->start();
        for(int j=0;j<newDay.size();j++)
        {
            loadedFile.append(newDay[j].splitRef('/').last());
            loadedFile.append("\n");
        }
    }
    if (count == 0) {
        emit complete();
    }
    lineEdit->setText(loadedFile);
}
inputControlling::~inputControlling()
{
}
void inputControlling::initializeBar()
{
    progressDialog=new QProgressDialog();
    QFont font("ZYSong18030",12);
    progressDialog->setFont(font);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setMinimumDuration(5);
    progressDialog->setWindowTitle(tr("Please Wait"));
    progressDialog->setLabelText(tr("Loading..."));
    progressDialog->setCancelButtonText(tr("Cancel"));
    progressDialog->setRange(0,75);
    progressDialog->setValue(0);
//    if(progressDialog->value()==75)
//        return;
//    if(progressDialog->wasCanceled())
//        return;
}
//Data inputControlling::importCSV(){    //this function is just for test
//    QFile file("D:/CS241FinalProject/updated Dataset/Dataset-CS241-2020/Dataset-CS241-2020/order_20161101_part0.csv");
//    Data data;
//    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
//        QTextStream in(&file);
//        QString line;
//        auto attr= in.readLine().splitRef(",");
//        while(in.readLineInto(&line)){
//            auto num=line.splitRef(",");
//            auto newsingle=OrderInformation(num[1].toInt(),
//                    num[2].toInt(),num[3].toDouble(),num[4].toDouble(),num[5].toDouble(),
//                    num[6].toDouble(), num[7].toDouble());
//            data.push_back(newsingle);
//        }
//    }
//    Dataset.push_back(data);
//    emit passing(&Dataset);
//    return data;
//}

//void inputControlling::startProgress()
//{
//    int num= Dataset.back().size();
//    QString number;
//    number.setNum(num);
//    QProgressDialog *progressDialog=new QProgressDialog(this);
//    QFont font("ZYSong18030",12);
//    progressDialog->setFont(font);
//    progressDialog->setWindowModality(Qt::WindowModal);
//    progressDialog->setMinimumDuration(5);
//    progressDialog->setWindowTitle(tr("Please Wait"));
//    progressDialog->setLabelText(tr("Loading..."));
//    progressDialog->setCancelButtonText(tr("Cancel"));
//    progressDialog->setRange(0,num);
//    for(int i=1;i<num+1;i++)
//    {
//        progressDialog->setValue(i);
//        if(progressDialog->wasCanceled())
//            return;
//    }
//}
//void inputControlling::slotStart()
//{
//    int num= Dataset.back().size();
//    theImportThread=new ProgressThread();
//    theImportThread->getNumber(num);
//    theImportThread->start();
//    //load the num to the thread
//}
//void inputControlling::slotStop()
//{
//    theImportThread->wait();
//}
//DataSet* inputControlling::passData(DataSet& dataset)
//{
//    DataSet *a=&dataset;
//    return a;
//}

