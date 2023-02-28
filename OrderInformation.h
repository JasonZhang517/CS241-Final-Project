#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H

#include <iostream>
#include <QString>
#include <QtDebug>
#include <QWidget>
#include <QDateTime>
class OrderInformation
{
    //data
public:
    // QString order_id;
//    int departure_time;
//    int end_time;
    double orig_lng;
    double orig_lat;
    double dest_lng;
    double dest_lat;
//    int orig_lnggrid;
//    int orig_latgrid;
//    int dest_lnggrid;
//    int dest_latgrid;

    double fee;
    int orig_gridid;
    int dest_gridid;
//    int departure_year,departure_month,departure_day;
//    int departure_hour,departure_minute,departure_second;
//    int end_year,end_month,end_day;
//    int end_hour,end_minute,end_second;
    QDateTime departure;
    QDateTime end;

    //functions
public:
    OrderInformation(int dtime=0, int etime=1, double olng=0,
    double olat=0,double dlng=1,double dlat=1,double cost=0);
    ~OrderInformation();
};
typedef QVector<OrderInformation> Data;
typedef QVector<Data*> DataSet;

#endif // ORDERINFORMATION_H
