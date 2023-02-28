#ifndef TRAVELTIME_H
#define TRAVELTIME_H
#include <Prediction.h>
class aChart:public QWidget{
    Q_OBJECT
public:
    explicit aChart(QWidget* parent=nullptr,int=0,int=0);
    ~aChart();
    DataSet savedData;
private:
    void updateChart();
private:
    void initLayout();
public:
    void loadData(const DataSet&);
    int begindate;
    int finishdate;
    QSpinBox* start;
    QSpinBox* end;
    QPushButton* informationBtn;
    QChart* chart;
    QChartView* chartView = new QChartView;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
    QVector<int> targetData1;
    QVector<int> targetData2;
    QVector<int> targetData3;
    QVector<int> targetData4;
    QVector<int> targetData5;
private slots:
    void showInformationMsg();
};
class Traveltime:public QWidget
{
    Q_OBJECT
public:
    explicit Traveltime(QWidget* parent=nullptr);
    ~Traveltime();
public:
    void loadData(const DataSet&);
    QListWidget *list;
    QStackedWidget *stack;
    aChart* chart1;
    aChart* chart2;
    aChart* chart3;
};


#endif // TRAVELTIME_H
