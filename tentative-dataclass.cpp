#include <iostream>
#include <QString>
#include <QtDebug>
#include <QWidget>
#include <QDateTime>
#include <OrderInformation.h>

OrderInformation::OrderInformation(int dtime, int etime, double olng,
double olat, double dlng, double dlat, double cost)
    : orig_lng(olng), orig_lat(olat), dest_lng(dlng), dest_lat(dlat), fee(cost),
      departure(QDateTime::fromSecsSinceEpoch(dtime)), end(QDateTime::fromSecsSinceEpoch(etime))
{
    int orig_lnggrid = (orig_lng - 103.9084) / 0.03136;
    int dest_lnggrid = (dest_lng - 103.9084) / 0.03136;
    int orig_latgrid = (orig_lat - 30.52408) / 0.02698;
    int dest_latgrid = (dest_lat - 30.52408) / 0.02698;
    if (orig_lnggrid > 9)
        orig_lnggrid = 9;
    if (orig_lnggrid < 0)
        orig_lnggrid = 0;
    if (dest_lnggrid > 9)
        dest_lnggrid = 9;
    if (dest_lnggrid < 0)
        dest_lnggrid = 0;
    orig_gridid = orig_latgrid * 10 + orig_lnggrid;
    dest_gridid = dest_latgrid * 10 + dest_lnggrid;
}

OrderInformation::~OrderInformation() {}
