#include "progressThread.h"
#include <QtDebug>
#include <QVector>
#include <QProgressDialog>
#include <QFont>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QSemaphore>
#include <QCoreApplication>
#include "ProgressDlg.h"


ProgressDlg::~ProgressDlg()
{
}
ProgressDlg::ProgressDlg(QWidget* parent): QDialog(parent)
{
}
//ProgressThread::ProgressThread()
//{
//}
//void ProgressThread::setNumber(int number)
//{
//    progressDialog->setValue(number);
//}
//void ProgressThread::getNumber(int number)
//{
//    myNumber=number;
//}
//void ProgressThread::run()
//{
//    progressDialog=new QProgressDialog();
//    QFont font("ZYSong18030",12);
//    progressDialog->setFont(font);
//    progressDialog->setWindowModality(Qt::WindowModal);
//    progressDialog->setMinimumDuration(5);
//    progressDialog->setWindowTitle(tr("Please Wait"));
//    progressDialog->setLabelText(tr("Loading..."));
//    progressDialog->setCancelButtonText(tr("Cancel"));
//    progressDialog->setRange(0,75);
//    progressDialog->setValue(0);
//    if(progressDialog->value()==75)
//        return;
//    if(progressDialog->wasCanceled())
//        return;
//}
importThread::importThread(QStringList& day)
{
    dayName=day;
}
void importThread::run()
{
    for(int i = 0; i < dayName.size(); i++)
    {
        QFile file(dayName[i]);
        auto data = new QVector<OrderInformation>;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString line;
            in.readLine();
            while(in.readLineInto(&line)) {
                auto num = line.splitRef(',');
                data->push_back(OrderInformation(num[1].toInt(),
                                num[2].toInt(),num[3].toDouble(),num[4].toDouble(),num[5].toDouble(),
                                num[6].toDouble(), num[7].toDouble()));
            }
            qDebug() << dayName[i] << "import complete!";
            emit release(data);
        }
    }
}
