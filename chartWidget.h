#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#endif // CHARTWIDGET_H
#include <QWidget>
#include <QtCharts>
#include<OrderInformation.h>

QT_CHARTS_USE_NAMESPACE

class ChartWidget: public QWidget{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget* = nullptr);
    ~ChartWidget();
    QComboBox *setStep;
    QSpinBox *timeStart;
    QSpinBox *timeEnd;
    QSpinBox *dayStart;
    QSpinBox *dayEnd;
    QLabel *monthDisplay;
    QLabel *yearDisplay;
    QLabel *FeeDisplay;
    QLineEdit *fieldStart;
    QLineEdit *fieldEnd;
    QPushButton *plotBtn;
    QChartView* chartView = nullptr;
    DataSet newData;
    double totalRevenue;
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
    QSpinBox* start = nullptr;
    QSpinBox* end = nullptr;

};
