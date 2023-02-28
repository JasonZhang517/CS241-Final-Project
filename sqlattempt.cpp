#include <QtCore>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
void createSql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("LAPTOP-GIUNUSKG");
    db.setDatabaseName("qtDB.db");
    db.setUserName("zhangyixin");
    db.setPassword("123456");
    db.open();
    QSqlQuery query;
    bool success=query.exec("create table orderInformation
                             (order_id varchar primary key,
                             departure_day int,
                             departure_hour int,
                             orig_lnggrid int,
                             orig_latgrid int
                             orig_grid int,
                             dest_lnggrid int,
                             dest_latrid int,
                             dest_grid int,
                             fee double)");

}
