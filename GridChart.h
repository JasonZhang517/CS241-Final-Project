#ifndef GRIDCHART_H
#define GRIDCHART_H

#endif // GRIDCHART_H
#include <QWidget>
#include <QtCharts>
#include<chartWidget.h>

class GridChart:public QWidget{
    Q_OBJECT
public:
    explicit GridChart(QWidget* =nullptr);
    ~GridChart();
    QSpinBox *timeStart;
    QSpinBox *timeEnd;
    QSpinBox *dayStart;
    QSpinBox *dayEnd;
    QLabel *monthDisplay;
    QLabel *yearDisplay;
    QLineEdit *fieldStart;
    QLineEdit *fieldEnd;
    QPushButton *plotBtn;
    QChartView* chartView = nullptr;
    DataSet newData;
private:
    void updateChart();
private:
    void initLayout();
public slots:
    void loadData();
private slots:
    void showInformationMsg();
public slots:
    void getData(const DataSet&);
private:
    QPushButton* informationBtn;
private:
    QVector<int> numberOfOrders;
};
