#ifndef PROGRESSTHREAD_H
#define PROGRESSTHREAD_H

#endif // PROGRESSTHREAD_H
#include <QThread>
#include <QProgressDialog>
#include <QWidget>
#include <OrderInformation.h>
//class ProgressThread : public QThread
//{
//    Q_OBJECT
//public:
//    ProgressThread();
//    void getNumber(int number);
//    QProgressDialog *progressDialog;
//private:
//    int myNumber;
//private slots:
//    void setNumber(int number);
//protected:
//    void run();
//};
class importThread: public QThread
{
    Q_OBJECT
public:
    importThread(QStringList&);
    QStringList dayName;
signals:
    void release(Data*);
protected:
    void run();
};
