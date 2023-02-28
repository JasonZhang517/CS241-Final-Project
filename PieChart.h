#ifndef PIECHART_H
#define PIECHART_H
#include <QWidget>
#include <QtCharts>
#include <GridChart.h>
class PieChart:public QWidget
{
    Q_OBJECT
public:
    explicit PieChart(QWidget* parent=nullptr);
    ~PieChart();
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
private slots:
    void displaySlice(QPieSlice* slice,bool status);
public slots:
    void loadData();
private slots:
    void showInformationMsg();
public slots:
    void getData(const DataSet&);
private:
    QPushButton* informationBtn;
    QPieSeries* pieSeries;
private:
    QVector<int> numberOfOrders;
};

#endif // PIECHART_H
